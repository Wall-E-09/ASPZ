#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define LOG_FILE "/var/log/signal_monitor.log"

void handle_signal(int signum, siginfo_t *info, void *context);
void daemonize(void);
void close_all_files(void);
void log_signal_details(int signum, siginfo_t *info);

int main()
{
    daemonize();

    // Налаштовуємо обробник сигналів з додатковою інформацією
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; // Використовуємо розширений обробник

    // Реєструємо обробники для всіх стандартних сигналів
    for (int sig = 1; sig < SIGRTMIN; sig++)
    {
        // Пропускаємо сигнали, які не можна перехопити
        if (sig == SIGKILL || sig == SIGSTOP)
            continue;

        if (sigaction(sig, &sa, NULL) == -1)
        {
            syslog(LOG_WARNING, "Failed to set handler for signal %d (%s)",
                   sig, strsignal(sig));
        }
    }

    syslog(LOG_INFO, "Signal monitoring daemon started successfully");

    while (1)
    {
        pause();
    }

    return 0;
}

void daemonize(void)
{
    pid_t pid;

    // 1. Створення дочірнього процесу
    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid != 0)
    {
        printf("Daemon started with PID: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    // 2. Дочірній процес продовжує роботу
    if (setsid() < 0)
    {
        syslog(LOG_ERR, "Failed to create new session");
        exit(EXIT_FAILURE);
    }

    // Ігноруємо SIGHUP
    signal(SIGHUP, SIG_IGN);

    // Другий fork для запобігання отримання контрольного терміналу
    if ((pid = fork()) < 0)
    {
        syslog(LOG_ERR, "Second fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid != 0)
    {
        exit(EXIT_SUCCESS);
    }

    // Змінюємо робочу директорію на кореневу
    if (chdir("/") < 0)
    {
        syslog(LOG_ERR, "Failed to change directory to /");
        exit(EXIT_FAILURE);
    }

    // Закриваємо всі файлові дескриптори
    close_all_files();

    // Перенаправляємо стандартні потоки вводу/виводу/помилок
    int fd = open("/dev/null", O_RDWR);
    if (fd != -1)
    {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO)
        {
            close(fd);
        }
    }

    // Встановлюємо маску прав для нових файлів
    umask(022);

    // Відкриття системного журналу
    openlog("signal-monitor", LOG_PID, LOG_LOCAL0);
}

void close_all_files(void)
{
    struct rlimit flim;
    getrlimit(RLIMIT_NOFILE, &flim);

    for (int fd = 0; fd < (int)flim.rlim_max; fd++)
    {
        close(fd);
    }
}

void handle_signal(int signum, siginfo_t *info, void *context)
{
    log_signal_details(signum, info);

    // Особлива обробка для SIGTERM - завершення роботи демона
    if (signum == SIGTERM)
    {
        syslog(LOG_INFO, "Received termination signal (SIGTERM), shutting down");
        closelog();
        exit(EXIT_SUCCESS);
    }
}

void log_signal_details(int signum, siginfo_t *info)
{
    time_t now;
    time(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    char signal_name[32];
    const char *sig_name = strsignal(signum);
    if (sig_name)
    {
        snprintf(signal_name, sizeof(signal_name), "%s", sig_name);
    }
    else
    {
        snprintf(signal_name, sizeof(signal_name), "SIG%d", signum);
    }

    // Відкриваємо файл журналу
    int fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        syslog(LOG_ERR, "Failed to open log file: %m");
        return;
    }

    // Формуємо запис журналу
    char log_entry[512];
    int len = snprintf(log_entry, sizeof(log_entry),
                       "[%s] Signal: %s (%d), Sender PID: %d, UID: %d, GID: %d\n",
                       timestamp, signal_name, signum, info->si_pid, info->si_uid, info->si_gid);

    // Додаткова інформація для реального часу сигналів
    if (signum >= SIGRTMIN && signum <= SIGRTMAX)
    {
        len += snprintf(log_entry + len, sizeof(log_entry) - len,
                        "    Signal value: %d\n", info->si_value.sival_int);
    }

    // Записуємо в журнал
    write(fd, log_entry, strlen(log_entry));
    close(fd);

    // Також записуємо в системний журнал для швидкого моніторингу
    syslog(LOG_INFO, "Signal %s received from PID %d (UID: %d)",
           signal_name, info->si_pid, info->si_uid);
}
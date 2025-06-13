#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LOG_FILE "/var/log/signal_monitor.log"

void log_signal(int sig, siginfo_t *info, void *context) {
    time_t now;
    time(&now);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp)-1] = '\0'; // Видаляємо \n
    
    int fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open log file failed");
        return;
    }
    
    char buf[256];
    int len = snprintf(buf, sizeof(buf), "[%s] Signal %d received from PID %d (UID: %d, GID: %d)\n",
                      timestamp, sig, info->si_pid, info->si_uid, info->si_gid);
    
    write(fd, buf, len);
    close(fd);
}

int main() {
    // Стаємо демоном
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid > 0) {
        exit(0); // Батьківський процес завершується
    }
    
    setsid(); // Створюємо нову сесію
    chdir("/"); // Змінюємо робочу директорію
    umask(0); // Скидаємо маску файлів
    
    // Перенаправляємо стандартні потоки
    close(STDIN_FILENO);
    close(STDOUT_FILENENO);
    close(STDERR_FILENO);
    
    // Налаштовуємо обробники для всіх сигналів
    struct sigaction sa;
    sa.sa_sigaction = log_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    
    // Реєструємо обробники для всіх стандартних сигналів
    for (int sig = 1; sig < SIGRTMIN; sig++) {
        // Пропускаємо сигнали, які не можна перехопити
        if (sig == SIGKILL || sig == SIGSTOP) continue;
        
        if (sigaction(sig, &sa, NULL) == -1) {
            // Не всі сигнали можна перехопити, ігноруємо помилки
        }
    }
    
    // Основний цикл демона
    while (1) {
        pause(); // Очікуємо сигнали
    }
    
    return 0;
}
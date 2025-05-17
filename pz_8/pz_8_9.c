#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Початковий процес PID: %d\n", getpid());
    
    for (int i = 0; i < 3; i++) {
        sleep(1);
        pid_t pid = fork();
        
        if (pid == 0) {
            printf("Дочірній [i=%d] PID: %d, PPID: %d\n", 
                   i, getpid(), getppid());
            sleep(3);
            _exit(0);
        } else if (pid > 0) {
            printf("Батьківський створив дитину PID: %d (i=%d)\n", pid, i);
        } else {
            perror("fork");
            return 1;
        }
    }
    
    while (wait(NULL) > 0);
    printf("Завершення основного процесу PID: %d\n", getpid());
    return 0;
}
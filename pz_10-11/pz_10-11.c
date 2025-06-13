#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 10

int main() {
    pid_t child_pids[NUM_CHILDREN];
    int i;

    // Створюємо 10 дочірніх процесів
    for (i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Дочірній процес
            printf("Child %d (PID: %d) started\n", i, getpid());
            sleep(i + 1); // Різний час роботи для кожного процесу
            printf("Child %d (PID: %d) exiting\n", i, getpid());
            exit(0);
        } else {
            // Батьківський процес - зберігаємо PID
            child_pids[i] = pid;
        }
    }

    // Очікуємо завершення всіх дочірніх процесів
    for (i = 0; i < NUM_CHILDREN; i++) {
        int status;
        pid_t terminated_pid = wait(&status);
        
        if (terminated_pid == -1) {
            perror("wait failed");
            continue;
        }
        
        // Знаходимо індекс процесу в масиві
        int child_index = -1;
        for (int j = 0; j < NUM_CHILDREN; j++) {
            if (child_pids[j] == terminated_pid) {
                child_index = j;
                break;
            }
        }
        
        if (WIFEXITED(status)) {
            printf("Child %d (PID: %d) exited with status %d\n", 
                   child_index, terminated_pid, WEXITSTATUS(status));
        } else {
            printf("Child %d (PID: %d) terminated abnormally\n", 
                   child_index, terminated_pid);
        }
    }

    printf("All children have exited\n");
    return 0;
}
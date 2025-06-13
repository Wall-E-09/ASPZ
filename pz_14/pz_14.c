#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <секунди>\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);
    if (seconds <= 0) {
        fprintf(stderr, "Час має бути додатнім числом\n");
        return 1;
    }

    printf("Таймер запущено на %d секунд...\n", seconds);

    struct timespec ts;
    ts.tv_sec = seconds;
    ts.tv_nsec = 0;
    
    int result = clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
    
    if (result != 0) {
        if (result == EINTR) {
            fprintf(stderr, "Таймер був перерваний\n");
        } else {
            perror("Помилка clock_nanosleep");
        }
        return 1;
    }

    printf("Час вийшов! (%d секунд минуло)\n", seconds);
    return 0;
}
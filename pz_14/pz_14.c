#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        return 1;
    }
    
    int seconds = atoi(argv[1]);
    if (seconds <= 0) {
        fprintf(stderr, "Please specify a positive number of seconds\n");
        return 1;
    }
    
    printf("Timer set for %d seconds\n", seconds);
    
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    ts.tv_sec += seconds;
    
    // Використовуємо абсолютний час для більшої точності
    while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, NULL) == EINTR) {
        // Якщо sleep був перерваний сигналом, продовжуємо
    }
    
    printf("Time's up! %d seconds have passed.\n", seconds);
    return 0;
}
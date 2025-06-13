#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);
    if (seconds <= 0) {
        fprintf(stderr, "Time must be a positive number\n");
        return 1;
    }

    printf("Timer started for %d seconds...\n", seconds);

    struct timespec ts;
    ts.tv_sec = seconds;
    ts.tv_nsec = 0;

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR) {
        // Restart if interrupted by signal
        continue;
    }

    printf("Time's up! (%d seconds elapsed)\n", seconds);
    return 0;
}
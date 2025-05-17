#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>
#include <unistd.h>

void handle_file_limit(int sig) {
    printf("Перевищено обмеження на розмір файлу\n");
    exit(1);
}

void set_file_limit(rlim_t size) {
    struct rlimit lim = {size, size};
    setrlimit(RLIMIT_FSIZE, &lim);
}

int main() {
    signal(SIGXFSZ, handle_file_limit);
    set_file_limit(3);  

    FILE *f = fopen("dice.txt", "w");
    if (!f) {
        perror("fopen");
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        int roll = rand() % 6 + 1;
        fprintf(f, "Кидок %d: %d\n", i+1, roll);
        fflush(f);
        usleep(10000); 
    }

    fclose(f);
    return 0;
}
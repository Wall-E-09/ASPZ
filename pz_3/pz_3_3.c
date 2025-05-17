#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>

#define MAX_CPU_TIME 2

void set_cpu_limit() {
    struct rlimit limit;
    limit.rlim_cur = MAX_CPU_TIME;
    limit.rlim_max = MAX_CPU_TIME;
    
    if (setrlimit(RLIMIT_CPU, &limit) == -1) {
        perror("Помилка встановлення обмеження CPU");
        exit(EXIT_FAILURE);
    }
}

void select_numbers(int *numbers, int count, int max) {
    int selected[max + 1];
    for (int i = 0; i <= max; i++) selected[i] = 0;
    
    for (int i = 0; i < count; ) {
        int num = rand() % max + 1;
        if (!selected[num]) {
            selected[num] = 1;
            numbers[i++] = num;
        }
    }
}

int main() {
    set_cpu_limit();
    
    srand(time(NULL));
    
    printf("Лотерейний симулятор (обмеження CPU: %d сек)\n", MAX_CPU_TIME);
    printf("----------------------------------------\n");
    
    int main_numbers[7], bonus_numbers[6];
    
    select_numbers(main_numbers, 7, 49);
    select_numbers(bonus_numbers, 6, 36);
    
    printf("7 з 49: ");
    for (int i = 0; i < 7; i++) printf("%d ", main_numbers[i]);
    
    printf("\n6 з 36: ");
    for (int i = 0; i < 6; i++) printf("%d ", bonus_numbers[i]);
    
    printf("Готово! Час CPU не перевищено.\n");
    
    return EXIT_SUCCESS;
}
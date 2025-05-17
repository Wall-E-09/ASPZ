#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>

#define FILENAME "dice_rolls.txt"
#define MAX_FILE_SIZE 1024  

void set_file_size_limit() {
    struct rlimit limit;
    limit.rlim_cur = MAX_FILE_SIZE; 
    limit.rlim_max = MAX_FILE_SIZE; 
    
    if (setrlimit(RLIMIT_FSIZE, &limit) == -1) {
        perror("Помилка встановлення обмеження на файл");
        exit(EXIT_FAILURE);
    }
}

void write_roll(FILE *file, int roll) {
    if (fprintf(file, "Кидок: %d\n", roll) < 0) {
        perror("Помилка запису у файл");
        exit(EXIT_FAILURE);
    }
    fflush(file); 
}

int main() {
    FILE *file;
    int roll;
    
    set_file_size_limit();
    
    file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Помилка відкриття файлу");
        return EXIT_FAILURE;
    }
    
    srand(time(NULL));
    
    printf("Симуляція кидків кубика...\n");
    printf("Файл: %s (максимальний розмір: %d байт)\n", FILENAME, MAX_FILE_SIZE);
    
    while (1) {
        roll = rand() % 6 + 1; 
        write_roll(file, roll);
        
        long pos = ftell(file);
        if (pos == -1) {
            perror("Помилка отримання позиції у файлі");
            break;
        }
        
        if (pos >= MAX_FILE_SIZE) {
            printf("\nДосягнуто максимальний розмір файлу (%d байт).\n", MAX_FILE_SIZE);
            break;
        }
        
        printf(".");
    }
    
    fclose(file);
    printf("\nРезультати збережено у файл: %s\n", FILENAME);
    return EXIT_SUCCESS;
}
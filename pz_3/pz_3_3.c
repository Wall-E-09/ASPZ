#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define FILENAME "dice_rolls.txt"
#define MAX_FILE_SIZE 1024

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
    long file_size = 0;

    file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Помилка відкриття файлу");
        return EXIT_FAILURE;
    }
    
    srand((unsigned int)time(NULL));
    
    printf("Симуляція кидків кубика...\n");
    printf("Файл: %s (максимальний розмір: %d байт)\n", FILENAME, MAX_FILE_SIZE);
    
    while (1) {
        roll = rand() % 6 + 1;
        write_roll(file, roll);
        
        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        if (file_size == -1) {
            perror("Помилка отримання розміру файлу");
            break;
        }
        
        if (file_size >= MAX_FILE_SIZE) {
            printf("\nДосягнуто максимальний розмір файлу (%d байт).\n", MAX_FILE_SIZE);
            break;
        }
        
        printf(".");
    }
    
    fclose(file);
    printf("\nРезультати збережено у файл: %s\n", FILENAME);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *directory = opendir(".");
    if (!directory) {
        perror("Не вдалось відкрити каталог");
        return 1;
    }

    struct dirent *file_entry;
    while ((file_entry = readdir(directory)) != NULL) {
        const char *ext = strrchr(file_entry->d_name, '.');
        if (ext && strcmp(ext, ".c") == 0) {
            printf("Знайдено файл: %s\n", file_entry->d_name);
            printf("Бажаєте додати дозвіл на читання іншим користувачам? (y/n): ");

            char answer = '\0';
            while ((answer = getchar()) == '\n'); 
            
            if (answer == 'y' || answer == 'Y') {
                struct stat file_info;
                if (stat(file_entry->d_name, &file_info) == 0) {
                    mode_t new_mode = file_info.st_mode | S_IROTH;
                    if (chmod(file_entry->d_name, new_mode) == 0) {
                        printf("Дозвіл на читання для інших додано.\n");
                    } else {
                        perror("Помилка зміни дозволів");
                    }
                } else {
                    perror("Не вдалося отримати інформацію про файл");
                }
            }
        }
    }

    closedir(directory);
    return 0;
}

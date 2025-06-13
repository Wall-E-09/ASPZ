#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    const char *src_file = "/tmp/testfile.txt";

    const char *home_dir = getenv("HOME");
    if (!home_dir) {
        fprintf(stderr, "Не вдалося визначити домашню теку користувача\n");
        return 1;
    }

    char dest_file[1024];
    snprintf(dest_file, sizeof(dest_file), "%s/copied_by_root.txt", home_dir);

    FILE *f = fopen(src_file, "w");
    if (f == NULL) {
        perror("Помилка створення файлу");
        return 1;
    }
    fprintf(f, "Тестовий файл створено звичайним користувачем\n");
    fclose(f);
    printf("Файл створено: %s\n", src_file);

    char command[2048];
    snprintf(command, sizeof(command), "sudo cp %s %s", src_file, dest_file);
    int res = system(command);
    if (res != 0) {
        fprintf(stderr, "Помилка копіювання файлу за допомогою sudo\n");
        return 1;
    }
    printf("Файл скопійовано до: %s\n", dest_file);

    snprintf(command, sizeof(command), "ls -l %s", dest_file);
    printf("\nІнформація про скопійований файл:\n");
    system(command);

    printf("\nСпроба додати текст до файлу...\n");
    f = fopen(dest_file, "a");
    if (f == NULL) {
        perror("Не вдалося відкрити файл для запису");
    } else {
        fprintf(f, "Додано текст звичайним користувачем\n");
        fclose(f);
        printf("Файл успішно змінено\n");
    }

    printf("\nСпроба видалити файл...\n");
    if (remove(dest_file) == 0) {
        printf("Файл успішно видалено\n");
    } else {
        perror("Не вдалося видалити файл");
    }

    return 0;
}

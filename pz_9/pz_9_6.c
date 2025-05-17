#include <stdio.h>
#include <stdlib.h>

void check_directory(const char *path) {
    printf("\nПеревірка каталогу: %s\n", path);
    printf("Власники та права доступу:\n");
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s | head -n 5", path);
    system(command);
    
    printf("\nСпроба створити файл:\n");
    snprintf(command, sizeof(command), "touch %s/testfile 2>&1", path);
    system(command);
    
    printf("\nСпроба прочитати випадковий файл:\n");
    snprintf(command, sizeof(command), "cat %s/* 2>&1 | head -n 3", path);
    system(command);
}

int main() {
    check_directory(getenv("HOME"));
    check_directory("/usr/bin");
    check_directory("/etc");
    
    return 0;
}
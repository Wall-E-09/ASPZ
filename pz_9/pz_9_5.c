#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    
    FILE *fp = fopen("tempfile.txt", "w");
    if (fp) {
        fprintf(fp, "Тимчасовий вміст\n");
        fclose(fp);
    } else {
        perror("Не вдалося створити файл");
        return 1;
    }
    
    system("sudo chown root:root tempfile.txt");
    system("sudo chmod 600 tempfile.txt");
    
    printf("Спроба читати файл:\n");
    system("cat tempfile.txt 2>&1");
    
    printf("\nСпроба записати у файл:\n");
    system("echo 'Новий вміст' >> tempfile.txt 2>&1");
    
    system("sudo rm -f tempfile.txt");
    
    return 0;
}
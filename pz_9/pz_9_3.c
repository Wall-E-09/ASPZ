#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    FILE *fp = fopen("testfile.txt", "w");
    if (fp) {
        fprintf(fp, "Тестовий вміст\n");
        fclose(fp);
    } else {
        perror("Не вдалося створити файл");
        return 1;
    }
    
    // Копіюємо файл як root
    system("sudo cp testfile.txt testfile_copy.txt");
    system("sudo chown root:root testfile_copy.txt");
    
    system("sudo mv testfile_copy.txt ~/");
    
    system("echo 'Новий вміст' >> ~/testfile_copy.txt 2>&1");
    
    system("rm ~/testfile_copy.txt 2>&1");
    
    return 0;
}
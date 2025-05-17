#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Спроба прочитати /etc/shadow:\n");
    
    int result = system("sudo cat /etc/shadow 2>&1");
    
    if (result != 0) {
        printf("Не вдалося прочитати файл (можливо, немає прав sudo).\n");
    }
    
    return 0;
}
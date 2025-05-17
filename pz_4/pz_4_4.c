#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buggy_version() {
    printf("=== BUGGY VERSION ===\n");
    void *ptr = NULL;
    int i = 0;
    
    while (i < 3) {
        if (!ptr) {
            ptr = malloc(16);
            printf("Allocated ptr = %p\n", ptr);
        }
        
        // Використовуємо пам'ять
        strcpy((char*)ptr, "Iteration ");
        ((char*)ptr)[10] = '0' + i;
        ((char*)ptr)[11] = '\0';
        printf("Using ptr: %s\n", (char*)ptr);
        
        free(ptr);
        i++;
    }
}

void correct_version() {
    printf("\n=== CORRECT VERSION 2 ===\n");
    void *ptr = malloc(16);
    if (!ptr) {
        perror("malloc failed");
        exit(1);
    }
    
    int i = 0;
    while (i < 3) {
        strcpy((char*)ptr, "Iteration ");
        ((char*)ptr)[10] = '0' + i;
        ((char*)ptr)[11] = '\0';
        printf("Using ptr: %s\n", (char*)ptr);
        i++;
    }
    
    free(ptr);  // Звільняємо тільки один раз
}

int main() {
    
    correct_version();

    //buggy_version();
    return 0;
}
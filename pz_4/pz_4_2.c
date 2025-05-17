#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 1000000;
    int xb = 1000000;
    int num = xa * xb;
    
    printf("Результат множення (int): %d\n", num);
    printf("Те ж саме як size_t: %zu\n", (size_t)num);
    
    void *ptr = malloc(num);
    if (ptr == NULL) {
        perror("malloc failed");
        printf("Причина: num як size_t = %zu\n", (size_t)num);
    } else {
        printf("malloc успішний (це дуже небезпечно!)\n");
        free(ptr);
    }
    
    return 0;
}
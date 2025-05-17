#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t max_size = SIZE_MAX;
    printf("Теоретичний максимум: %zu байт (~%.2f EB)\n", 
           max_size, (double)max_size / (1024 * 1024 * 1024 * 1024 * 1024 * 1024));

    void *ptr = malloc(max_size);
    if (ptr == NULL) {
        perror("malloc failed");
        printf("Фактичний максимум менший за теоретичний\n");
    } else {
        free(ptr);
    }
    
    return 0;
}
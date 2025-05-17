#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    
    // Код для вимірювання
    for (int i = 0; i < 1000000; i++);
    
    clock_t end = clock();
    double time = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    printf("Time: %.2f ms\n", time);
    return 0;
}
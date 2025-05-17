#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void test_qsort(int *arr, int size) {
    clock_t start = clock();
    qsort(arr, size, sizeof(int), compare);
    clock_t end = clock();
    printf("Час сортування: %.2f мс\n", (double)(end-start)*1000/CLOCKS_PER_SEC);
}

int main() {
    int size = 10000;
    int *arr = malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) arr[i] = i;
    test_qsort(arr, size);
    
    for (int i = 0; i < size; i++) arr[i] = 42;
    test_qsort(arr, size);
    
    for (int i = 0; i < size; i++) arr[i] = size - i;
    test_qsort(arr, size);
    
    free(arr);
    return 0;
}
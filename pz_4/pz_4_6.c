#include <stdio.h>
#include <stdlib.h>

void test_realloc_edge_cases() {
    printf("=== realloc(NULL, size) test ===\n");
    void *ptr1 = realloc(NULL, 100);
    printf("ptr1 = %p\n", ptr1);
    
    printf("\n=== realloc(ptr, 0) test ===\n");
    void *ptr2 = malloc(100);
    printf("Before: ptr2 = %p\n", ptr2);
    void *ptr3 = realloc(ptr2, 0);
    printf("After: ptr3 = %p\n", ptr3);
    
    printf("\n=== Додаткова перевірка ===\n");
    void *ptr4 = malloc(100);
    void *ptr5 = realloc(ptr4, 0);
    if (ptr5 == NULL) {
        printf("ptr4 був звільнений (не використовуйте його!)\n");
    }
}

int main() {
    test_realloc_edge_cases();
    return 0;
}
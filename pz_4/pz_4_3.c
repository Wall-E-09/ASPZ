#include <stdio.h>
#include <stdlib.h>

void test_malloc_zero() {
    void *ptr1 = malloc(0);
    void *ptr2 = malloc(0);
    
    printf("ptr1 (%p) is %s\n", ptr1, ptr1 ? "not NULL" : "NULL");
    printf("ptr2 (%p) is %s\n", ptr2, ptr2 ? "not NULL" : "NULL");
    
    if (ptr1) free(ptr1);
    if (ptr2) free(ptr2);
    
    printf("After free()\n");
}

int main() {
    test_malloc_zero();
    return 0;
}
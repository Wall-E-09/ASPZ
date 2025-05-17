#include <stdio.h>

#define SIZE 1000000 


int global_array[SIZE];

int main() {
    printf("Розмір масиву: %zu MB\n", sizeof(global_array) / (1024 * 1024));
    printf("Адреса масиву: %p (у BSS)\n", global_array);
    
    
    global_array[0] = 42;
    printf("Перший елемент: %d\n", global_array[0]);
    
    return 0;
}

//gcc bss_demo.c -o bss_demo && size ./bss_demo
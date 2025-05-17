//gcc pz_2_3.c -o pz_2_3 && ./pz_2_3
 

#include <stdio.h>
#include <stdlib.h>

int global_var = 10;            
static int static_var = 20;     
int uninit_global_var;          
static int uninit_static_var;   

void test_stack_growth(int depth) {
    int local_var;
    int large_array[1024];  
    
    printf("Stack frame %d: %p\n", depth, &local_var);
    
    if (depth > 0) {
        test_stack_growth(depth - 1);  
    }
}

int main() {
    int local_main;  
    int *heap_var = malloc(sizeof(int));  
    
    printf("1. Text segment (адреса функції): %p\n", (void*)main);
    printf("2. Data segment (ініціалізовані глобальні):\n");
    printf("   global_var: %p\n", &global_var);
    printf("   static_var: %p\n", &static_var);
    printf("3. BSS segment (неініціалізовані глобальні):\n");
    printf("   uninit_global_var: %p\n", &uninit_global_var);
    printf("   uninit_static_var: %p\n", &uninit_static_var);
    printf("4. Heap (динамічна пам'ять): %p\n", heap_var);
    printf("5. Stack (локальна змінна в main): %p\n", &local_main);
    
    
    printf("Вершина стека в main(): %p\n", &local_main);
    printf("Адреса при вході в функцію:\n");
    test_stack_growth(3);  
    
    
    free(heap_var);
    
    return 0;
}
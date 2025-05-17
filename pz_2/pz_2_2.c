#include <stdio.h>


// gcc pz_2_2.c -o pz_2_2 && ./pz_2_2

void stage1(void) {
    printf("Hello, world!\n");
}

// gcc pz_2_2.c -o pz_2_2 && size ./pz_2_2


int global_array[1000];  //BSS сегмент

void stage2(void) {
    printf("Розмір масиву: %zu байт\n", sizeof(global_array));
}

// gcc pz_2_2.c -o pz_2_2 && size ./pz_2_2


int global_init_array[1000] = {1};

void stage3(void) {
    printf("Розмір масиву: %zu байт\n", sizeof(global_init_array));
}

// gcc pz_2_2.c -o pz_2_2 && size ./pz_2_2

void stage4(void) {
    int local_array[1000];
    int local_init_array[1000] = {0}; // Стек
    
    printf("Адреси: %p (неініціалізований), %p (ініціалізований)\n",
           local_array, local_init_array);
}

// gcc -g pz_2_2.c -o pz_2_2_debug && size ./pz_2_2_debug
// gcc -O3 pz_2_2.c -o pz_2_2_opt && size ./pz_2_2_opt



int main() {
    stage1();
    stage2();
    stage3();
    stage4();

    return 0;
}
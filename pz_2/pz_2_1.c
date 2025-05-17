#include <stdio.h>
#include <time.h>
#include <limits.h>


int global_init = 10;
int global_uninit;
static int static_init = 5;
static int static_uninit;

void analyze_time_t() {
    printf("\nРозмір time_t: %zu байт\n", sizeof(time_t));
    
    if (sizeof(time_t) == 4) {
        time_t max_time = (time_t)((1UL << 31) - 1);
        printf("32-бітна система: максимальний time_t = %lld\n", 
              (long long)max_time);
        printf("Відповідає даті: %s", ctime(&max_time));
    } else if (sizeof(time_t) == 8) {
        time_t max_time = (time_t)((1ULL << 63) - 1);
        printf("64-бітна система: максимальний time_t = %lld\n", 
              (long long)max_time);
        printf("Відповідає даті: %s", ctime(&max_time));
    }
}

void analyze_memory_segments() {
    printf("\nАналіз сегментів пам'яті\n");
    int local_var; 
    
    printf("Адреси змінних:\n");
    printf("1. global_init (data):   %p\n", &global_init);
    printf("2. static_init (data):   %p\n", &static_init);
    printf("3. global_uninit (BSS):  %p\n", &global_uninit);
    printf("4. static_uninit (BSS):  %p\n", &static_uninit);
    printf("5. local_var (стек):     %p\n", &local_var);
}

int main() {
    analyze_time_t();
    analyze_memory_segments();
    
    return 0;
}

    //gcc -m32 pz_2_1.c -o pz32\n
    //gcc pz_2_1.c -o pz64\n
    
    //./pz32\n
    //./pz64\n
    
    //size pz32 pz64\n
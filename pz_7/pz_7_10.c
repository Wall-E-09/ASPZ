#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    
    srand(time(NULL));
    float n = atof(argv[1]);
    
    for (int i = 0; i < 10; i++) {
        printf("%f\n", (float)rand() / RAND_MAX * n);
    }
    
    return 0;
}
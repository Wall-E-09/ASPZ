#include <stdio.h>
#include <stdlib.h>

int* allocation() {
    int* var = malloc(sizeof(int));
    if (var) *var = 42;
    return var;
}

void safe_fill(int* buf) {
    if (buf) *buf = 42;
}

int main() {
    int* ptr1 = allocation();
    if (ptr1) {
        printf("Heap allocated: %d\n", *ptr1);
        free(ptr1);
    }

    int stack_var;
    safe_fill(&stack_var);
    printf("Stack variable: %d\n", stack_var);

    return 0;
}
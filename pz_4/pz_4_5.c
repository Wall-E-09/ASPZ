#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_realloc_fail() {
    char *ptr = malloc(100);
    if (!ptr) {
        perror("Initial malloc failed");
        return;
    }
    strcpy(ptr, "Important data");
    printf("Original: %p -> '%s'\n", (void*)ptr, ptr);

    char *new_ptr = realloc(ptr, 1UL << 40); 
    
    if (!new_ptr) {
        perror("realloc failed");
        printf("Old pointer %p is STILL VALID: '%s'\n", (void*)ptr, ptr);
        
        strcat(ptr, " (modified after realloc fail)");
        printf("Modified old ptr: '%s'\n", ptr);
        
        free(ptr);
    } else {
        printf("New pointer: %p\n", (void*)new_ptr);
        free(new_ptr);
    }
}

void test_fragmentation() {
    void *blocks[1000];
    for (int i = 0; i < 1000; i++) {
        blocks[i] = malloc(1024);
    }
    
    char *ptr = malloc(100);
    strcpy(ptr, "Fragmentation test");
    
    char *new_ptr = realloc(ptr, 1 << 20); 
    
    if (!new_ptr) {
        printf("realloc failed (fragmentation), but old ptr %p works: '%s'\n", 
               ptr, ptr);
        free(ptr);
    }
    
    for (int i = 0; i < 1000; i++) free(blocks[i]);
}

int main() {
    test_realloc_fail();
    test_fragmentation();
    return 0;
}
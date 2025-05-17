#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define MEMORY_POOL_SIZE (1024 * 1024)

typedef struct block {
    size_t size;
    struct block *next;
    int is_free;
} block_t;

static char memory_pool[MEMORY_POOL_SIZE];
static block_t *free_list = NULL;

void initialize_allocator() {
    free_list = (block_t*)memory_pool;
    free_list->size = MEMORY_POOL_SIZE - sizeof(block_t);
    free_list->next = NULL;
    free_list->is_free = 1;
}

void split_block(block_t *curr, size_t size) {
    if (curr->size > size + sizeof(block_t)) {
        block_t *new_block = (block_t*)((char*)curr + sizeof(block_t) + size);
        new_block->size = curr->size - size - sizeof(block_t);
        new_block->next = curr->next;
        new_block->is_free = 1;
        
        curr->size = size;
        curr->next = new_block;
    }
}

void *my_malloc(size_t size) {
    if (size == 0 || free_list == NULL) {
        return NULL;
    }

    block_t *curr = free_list;
    block_t *prev = NULL;
    
    while (curr != NULL && !(curr->is_free && curr->size >= size)) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return NULL;
    }

    split_block(curr, size);
    
    curr->is_free = 0;
    
    return (void*)(curr + 1);
}

void merge_blocks() {
    block_t *curr = free_list;
    while (curr != NULL && curr->next != NULL) {
        if (curr->is_free && curr->next->is_free && 
            (char*)curr + sizeof(block_t) + curr->size == (char*)curr->next) {
            curr->size += sizeof(block_t) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    block_t *block = (block_t*)ptr - 1;
    block->is_free = 1;
    
    merge_blocks();
}

int main() {
    initialize_allocator();
    
    printf("Custom memory allocator demo (free list based)\n");
    printf("Total memory pool: %d bytes\n", MEMORY_POOL_SIZE);
    
    int *arr1 = (int*)my_malloc(10 * sizeof(int));
    printf("Allocated array of 10 ints at %p\n", (void*)arr1);
    
    char *str = (char*)my_malloc(100);
    printf("Allocated string buffer at %p\n", (void*)str);
    
    my_free(arr1);
    printf("Freed int array\n");
    

    double *arr2 = (double*)my_malloc(5 * sizeof(double));
    printf("Allocated array of 5 doubles at %p\n", (void*)arr2);
    
    my_free(str);
    my_free(arr2);
    
    return 0;
}
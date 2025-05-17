#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_FILE "memory_access.log"

void log_access(const char* action, void* ptr, const char* type, const void* value, size_t size) {
    FILE* log = fopen(LOG_FILE, "a");
    if (!log) return;
    
    fprintf(log, "[%lu] %s at %p (as %s): ", (unsigned long)time(NULL), action, ptr, type);
    
    if (value) {
        for (size_t i = 0; i < size; i++) {
            fprintf(log, "%02x ", ((const unsigned char*)value)[i]);
        }
    }
    fprintf(log, "\n");
    fclose(log);
}

int main() {
    remove(LOG_FILE);
    
    int* int_ptr = malloc(sizeof(int));
    *int_ptr = 0xDEADBEEF;
    log_access("Allocated", int_ptr, "int", int_ptr, sizeof(int));
    
    double* double_ptr = (double*)int_ptr;
    *double_ptr = 3.141592653589793;
    log_access("Written  ", double_ptr, "double", double_ptr, sizeof(double));
    
    int corrupted_value = *int_ptr;
    log_access("Read     ", int_ptr, "int", &corrupted_value, sizeof(int));
    
    printf("int value after double write: %X\n", corrupted_value);
    
    free(int_ptr);
    return 0;
}
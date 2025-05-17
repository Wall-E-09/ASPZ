#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int id;
};

int main() {
    size_t initial_count = 1000;
    struct sbar *buffer = calloc(initial_count, sizeof(struct sbar));
    if (!buffer) {
        perror("Помилка при calloc");
        return 1;
    }

    printf("Виділено %zu елементів за адресою: %p\n", initial_count, buffer);

    size_t reduced_count = 500;
    struct sbar *resized_buffer = reallocarray(buffer, reduced_count, sizeof(struct sbar));

    if (!resized_buffer) {
        perror("Помилка при reallocarray");
        free(buffer);
        return 1;
    }

    printf("Змінено розмір до %zu елементів за адресою: %p\n", reduced_count, resized_buffer);
    free(resized_buffer);

    return 0;
}
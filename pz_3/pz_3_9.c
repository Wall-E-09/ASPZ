#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

#define MAX_FILE_SIZE (1024 * 1024) 
#define MAX_MEMORY (64 * 1024 * 1024)

void set_limits() {
    struct rlimit file_limit = {
        .rlim_cur = MAX_FILE_SIZE,
        .rlim_max = MAX_FILE_SIZE
    };
    if (setrlimit(RLIMIT_FSIZE, &file_limit) == -1) {
        perror("Failed to set file size limit");
        exit(EXIT_FAILURE);
    }

    struct rlimit mem_limit = {
        .rlim_cur = MAX_MEMORY,
        .rlim_max = MAX_MEMORY
    };
    if (setrlimit(RLIMIT_DATA, &mem_limit) == -1) {
        perror("Failed to set memory limit");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    set_limits();

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        fprintf(stderr, "Cannot open '%s' for reading\n", argv[1]);
        return EXIT_FAILURE;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (!dst) {
        fprintf(stderr, "Cannot open '%s' for writing\n", argv[2]);
        fclose(src);
        return EXIT_FAILURE;
    }

    char *buffer = malloc(1024 * 1024);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(src);
        fclose(dst);
        return EXIT_FAILURE;
    }

    size_t total = 0;
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src))) {
        if (fwrite(buffer, 1, bytes, dst) != bytes) {
            fprintf(stderr, "Write error to '%s'\n", argv[2]);
            break;
        }
        total += bytes;
        
        if (total > MAX_FILE_SIZE) {
            fprintf(stderr, "File size limit exceeded (%d bytes)\n", MAX_FILE_SIZE);
            break;
        }
    }

    free(buffer);
    fclose(src);
    fclose(dst);

    if (ferror(src)) {
        fprintf(stderr, "Read error from '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("Copied %zu bytes successfully\n", total);
    return EXIT_SUCCESS;
}
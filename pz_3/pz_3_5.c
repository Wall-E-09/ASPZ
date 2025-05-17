#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

#define MAX_FILE_SIZE (1024 * 1024)

void set_file_size_limit() {
    struct rlimit limit;
    limit.rlim_cur = MAX_FILE_SIZE;
    limit.rlim_max = MAX_FILE_SIZE;
    if (setrlimit(RLIMIT_FSIZE, &limit) == -1) {
        perror("Failed to set file size limit");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Program need two arguments\n");
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    set_file_size_limit();

    FILE *src = fopen(argv[1], "rb");
    if (src == NULL) {
        fprintf(stderr, "Cannot open file '%s' for reading\n", argv[1]);
        return EXIT_FAILURE;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (dst == NULL) {
        fprintf(stderr, "Cannot open file '%s' for writing\n", argv[2]);
        fclose(src);
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytes_read;
    long total_bytes = 0;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dst);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Write error to file '%s'\n", argv[2]);
            fclose(src);
            fclose(dst);
            return EXIT_FAILURE;
        }

        total_bytes += bytes_written;
        if (total_bytes > MAX_FILE_SIZE) {
            fprintf(stderr, "File size limit exceeded (max %d bytes)\n", MAX_FILE_SIZE);
            fclose(src);
            fclose(dst);
            return EXIT_FAILURE;
        }
    }

    if (ferror(src)) {
        fprintf(stderr, "Read error from file '%s'\n", argv[1]);
        fclose(src);
        fclose(dst);
        return EXIT_FAILURE;
    }

    fclose(src);
    fclose(dst);

    printf("File copied successfully (%ld bytes)\n", total_bytes);
    return EXIT_SUCCESS;
}
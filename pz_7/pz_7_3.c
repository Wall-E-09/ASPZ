#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    
    FILE *file = fopen(argv[2], "r");
    char line[256];
    
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, argv[1])) printf("%s", line);
    }
    
    fclose(file);
    return 0;
}
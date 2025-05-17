#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        char line[256];
        int count = 0;
        
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            if (++count % 20 == 0) getchar();
        }
        
        fclose(file);
    }
    return 0;
}
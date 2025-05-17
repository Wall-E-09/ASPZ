#include <stdio.h>

int main() {
    FILE *pipe = popen("rwho | more", "r");
    if (!pipe) return 1;
    pclose(pipe);
    return 0;
}
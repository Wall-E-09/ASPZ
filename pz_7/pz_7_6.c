#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat statbuf;
    char *subdirs[1000];
    int count = 0;
    
    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode) {
            subdirs[count] = strdup(entry->d_name);
            count++;
        }
    }
    
    qsort(subdirs, count, sizeof(char *), compare);
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", subdirs[i]);
        free(subdirs[i]);
    }
    
    closedir(dir);
    return 0;
}
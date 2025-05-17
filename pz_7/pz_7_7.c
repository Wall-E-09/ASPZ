#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat statbuf;
    char *files[1000];
    int count = 0;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c")) {
            files[count] = strdup(entry->d_name);
            count++;
        }
    }
    
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i+1, files[i]);
    }
    
    printf("Grant read permission? (y/n): ");
    char answer;
    scanf("%c", &answer);
    
    if (answer == 'y') {
        for (int i = 0; i < count; i++) {
            chmod(files[i], 0644);
            free(files[i]);
        }
    }
    
    closedir(dir);
    return 0;
}
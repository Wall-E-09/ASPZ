#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char answer;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
            
        printf("Delete %s? (y/n/a): ", entry->d_name);
        scanf(" %c", &answer);
        
        if (answer == 'y') remove(entry->d_name);
        else if (answer == 'a') {
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;
                remove(entry->d_name);
            }
            break;
        }
    }
    
    closedir(dir);
    return 0;
}
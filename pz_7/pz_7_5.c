#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void list_files(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat statbuf;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
            
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        stat(fullpath, &statbuf);
        
        printf("%s\n", fullpath);
        if (S_ISDIR(statbuf.st_mode)) list_files(fullpath);
    }
    
    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
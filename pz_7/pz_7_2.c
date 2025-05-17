#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat file_stat;
    
    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &file_stat);
        print_permissions(file_stat.st_mode);
        printf(" %ld %s\n", (long)file_stat.st_size, entry->d_name);
    }
    
    closedir(dir);
    return 0;
}
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_dirs(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    char fullpath[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode)) {
            printf("%s\n", fullpath);
            list_dirs(fullpath);  
        }
    }

    closedir(dir);
}

int main() {
    list_dirs(".");
    return 0;
}

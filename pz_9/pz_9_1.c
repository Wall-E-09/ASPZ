#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

int main() {
    struct passwd *pw;
    uid_t current_uid = getuid();
    const uid_t min_uid = 1000;
    
    struct passwd *current_pw = getpwuid(current_uid);
    if (!current_pw) {
        perror("getpwuid");
        return 1;
    }

    printf("Поточний користувач: %s (UID: %d)\n", current_pw->pw_name, current_uid);
    printf("Звичайні користувачі (UID >= %d, крім поточного):\n", min_uid);
    
    setpwent(); 
    
    int count = 0;
    while ((pw = getpwent()) != NULL) {
        if (pw->pw_uid >= min_uid && pw->pw_uid != current_uid) {
            printf("Користувач: %-16s UID: %-8d Домашній каталог: %s\n", 
                   pw->pw_name, pw->pw_uid, pw->pw_dir);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Інших звичайних користувачів не знайдено.\n");
    } else {
        printf("Знайдено %d звичайних користувачів.\n", count);
    }
    
    endpwent();
    
    return 0;
}
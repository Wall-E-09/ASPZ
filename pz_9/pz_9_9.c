#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

void test_identical_uids() {
    
    system("sudo useradd -u 10000 -m testuser1 2>/dev/null");
    system("sudo useradd -u 10000 -m testuser2 2>/dev/null");
    
    printf("\nПерелік тестових користувачів:\n");
    system("getent passwd testuser1 testuser2");
    
    printf("\nСтворюємо файл як testuser1:\n");
    system("sudo -u testuser1 touch /home/testuser1/testfile");
    system("sudo -u testuser1 chmod 600 /home/testuser1/testfile");
    system("ls -l /home/testuser1/testfile");
    
    printf("\nСпроба змінити файл як testuser2:\n");
    system("sudo -u testuser2 echo 'test' >> /home/testuser1/testfile 2>&1");
    system("ls -l /home/testuser1/testfile");
    
    printf("\nПеревірка ідентифікації:\n");
    system("sudo -u testuser1 whoami");
    system("sudo -u testuser2 whoami");
    system("sudo -u testuser1 id");
    system("sudo -u testuser2 id");
    
    printf("\nОчищення тестових даних:\n");
    system("sudo userdel -r testuser1 2>/dev/null");
    system("sudo userdel -r testuser2 2>/dev/null");
}

int main() {
    if (getuid() != 0) {
        
    }
    
    test_identical_uids();
    
    return 0;
}
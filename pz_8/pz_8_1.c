#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    char buffer[] = "Hello, world!";
    int nbytes = sizeof(buffer);
    int count = write(fd, buffer, nbytes);
    
    printf("Запрошено %d байт, записано %d байт\n", nbytes, count);
    close(fd);
    return 0;
}
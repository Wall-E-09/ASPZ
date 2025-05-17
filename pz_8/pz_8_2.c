#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    unsigned char data[] = {4,5,2,2,3,3,7,9,1,5};
    int fd = open("data.bin", O_WRONLY | O_CREAT, 0644);
    write(fd, data, sizeof(data));
    close(fd);

    fd = open("data.bin", O_RDONLY);
    lseek(fd, 3, SEEK_SET);
    unsigned char buffer[4];
    read(fd, buffer, 4);
    
    printf("Буфер містить: ");
    for (int i = 0; i < 4; i++) printf("%d ", buffer[i]);
    close(fd);
    return 0;
}
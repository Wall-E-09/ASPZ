#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_host_alive(const char *ip) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 1 -W 1 %s > /dev/null 2>&1", ip);
    return system(cmd) == 0;
}

bool is_port_open(const char *ip, int port) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "nc -z -w 1 %s %d > /dev/null 2>&1", ip, port);
    return system(cmd) == 0;
}

void scan_ports(const char *ip, int start_port, int end_port) {
    if (!is_host_alive(ip)) {
        printf("Хост %s недоступний!\n", ip);
        return;
    }

    printf("Сканування %s (порти %d-%d)...\n", ip, start_port, end_port);

    for (int port = start_port; port <= end_port; port++) {
        if (is_port_open(ip, port)) {
            printf("Порт %d відкритий\n", port);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Використання: %s <IP> <початковий порт> <кінцевий порт>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    scan_ports(ip, start_port, end_port);
    return 0;
}
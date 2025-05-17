#include <stdio.h>

void func1() {
    printf("func1: Адреса повернення у стеку\n");
}

void func2() {
    int x = 42; // Локальна змінна у стеку
    printf("func2: x = %d (адреса: %p)\n", x, &x);
    func1();
}

int main() {
    printf("main: Початок\n");
    func2();
    printf("main: Кінець\n");
    return 0;
}
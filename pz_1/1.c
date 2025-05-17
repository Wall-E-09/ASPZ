#include <stdio.h>

int replace(char *str, char replacement) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "The cat sat";
    char replacement;

    printf("Вхідний рядок: \"%s\"\n", str);
    printf("Введіть символ для заміни пробілів: ");
    scanf("%c", &replacement);

    int replacements = replace(str, replacement);
    printf("Результат: \"%s\"\n", str);
    printf("Кількість замін: %d\n", replacements);

    return 0;
}
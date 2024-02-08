#include <stdio.h>

void printInteger(int number) {
    if (number < 0) {
        putchar('-');
        number = -number;
    }

    if (number == 0) {
        puts("0");
        return;
    }

    char digits[11]; // Maximum digits for a 32-bit integer

    int numDigits = 0;
    while (number > 0) {
        digits[numDigits++] = number % 10 + '0';
        number /= 10;
    }

    for (int i = numDigits - 1; i >= 0; i--) {
        putchar(digits[i]);
    }
}

int main() {
    int num = 0;

    printInteger(num);

    return 0;
}


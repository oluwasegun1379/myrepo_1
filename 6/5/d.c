#include <stdio.h>

void printInteger(int number) {
    if (number < 0) {
        putchar('-');
        number = -number;
    }

    if (number == 0) {
        putchar('0');
        return;
    }

    int numDigits = 0;
    int temp = number;

    while (temp > 0) {
        temp /= 10;
        numDigits++;
    }

    char digits[numDigits];

    for (int i = numDigits - 1; i >= 0; i--) {
        digits[i] = number % 10 + '0';
        number /= 10;
    }

    for (int i = 0; i < numDigits; i++) {
        putchar(digits[i]);
    }
}

int main() {
    int num = 0;

    printInteger(num);

    return 0;
}


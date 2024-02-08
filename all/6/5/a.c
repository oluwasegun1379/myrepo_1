#include <stdio.h>

int main() {
    int value = 42;

    // Write the value to a file
    FILE* file = fopen("value.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", value);
        fclose(file);
    }

    // Rest of your program

    return 0;
}


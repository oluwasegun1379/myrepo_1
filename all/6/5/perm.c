#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void permutations(int arr[], int start, int end, int r, int pass) {
    if (start == r) {
        int i;
        for (i = 0; i < r; i++) {
            if (arr[i] != pass)
                break;
        }
        if (i == r)
            printArray(arr, r);
        return;
    }

    for (int i = start; i < end; i++) {
        swap(&arr[start], &arr[i]);
        permutations(arr, start + 1, end, r, pass);
        swap(&arr[start], &arr[i]); // backtrack
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int r = 4;
    int pass = 1379;  // Change the pass value to match your desired value

    permutations(arr, 0, n, r, pass);

    return 0;
}


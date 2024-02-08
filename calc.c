#include <stdio.h>
#include <math.h>

int main() {
    double num1, num2, result;
    int choice;
    
    printf("Scientific Calculator\n");
    printf("---------------------\n");
    
    printf("Enter the first number: ");
    scanf("%lf", &num1);
    
    printf("Enter the second number: ");
    scanf("%lf", &num2);
    
    printf("\n");
    
    printf("Select an operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Power\n");
    printf("6. Square root\n");
    
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    printf("\n");
    
    switch (choice) {
        case 1:
            result = num1 + num2;
            printf("Result: %.2lf\n", result);
            break;
        case 2:
            result = num1 - num2;
            printf("Result: %.2lf\n", result);
            break;
        case 3:
            result = num1 * num2;
            printf("Result: %.2lf\n", result);
            break;
        case 4:
            if (num2 != 0) {
                result = num1 / num2;
                printf("Result: %.2lf\n", result);
            } else {
                printf("Error: Division by zero!\n");
            }
            break;
        case 5:
            //result = pow(num1, num2);
            printf("Result: %.2lf\n", result);
            break;
        case 6:
            result = sqrt(num1);
            printf("Square root of %.2lf: %.2lf\n", num1, result);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
    
    return 0;
}

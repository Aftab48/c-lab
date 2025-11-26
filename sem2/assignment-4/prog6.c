#include <stdio.h>

int binaryToDecimal(int binary) {
    if (binary == 0)
        return 0;
    else
        return (binary % 10) + 2 * binaryToDecimal(binary / 10);
}

void decimalToBinary(int decimal) {
    if (decimal == 0)
        return;
    decimalToBinary(decimal / 2);
    printf("%d", decimal % 2);
}

int main() {
    int choice, num;

    printf("Choose conversion:\n1. Binary to Decimal\n2. Decimal to Binary\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter binary number: ");
        scanf("%d", &num);
        printf("Decimal: %d\n", binaryToDecimal(num));
    } else if (choice == 2) {
        printf("Enter decimal number: ");
        scanf("%d", &num);
        if (num == 0)
            printf("Binary: 0\n");
        else {
            printf("Binary: ");
            decimalToBinary(num);
            printf("\n");
        }
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
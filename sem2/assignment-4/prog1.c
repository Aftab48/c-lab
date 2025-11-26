#include <stdio.h>

void swapByValue(int a, int b) {
    printf("Before swapByValue - x: %d, y: %d\n", a, b);
    int temp = a;
    a = b;
    b = temp;
    printf("Inside swapByValue - x: %d, y: %d\n", a, b);
}

void swapByReference(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x,y;
    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);

    // Call by Value
    swapByValue(x, y);

    // Call by Reference
    printf("Before swapByReference - x: %d, y: %d\n", x, y);
    swapByReference(&x, &y);
    printf("After swapByReference - x: %d, y: %d\n", x, y);

    return 0;
}

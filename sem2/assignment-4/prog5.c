#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int n, r;
    printf("Enter values of n and r: ");
    scanf("%d %d", &n, &r);

    if (n < r) {
        printf("Invalid input: n should be greater than or equal to r.\n");
        return 1;
    }

    int nPr = factorial(n) / factorial(n - r);
    int nCr = factorial(n) / (factorial(r) * factorial(n - r));

    printf("nPr = %d\n", nPr);
    printf("nCr = %d\n", nCr);

    return 0;
}
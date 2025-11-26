#include <stdio.h>

int power(int x, int n) {
    if (n == 0)
        return 1;
    else
        return x * power(x, n - 1);
}

int main() {
    int base, exponent;
    printf("Enter base and exponent: ");
    scanf("%d %d", &base, &exponent);

    printf("%d raised to the power %d is %d\n", base, exponent, power(base, exponent));

    return 0;
}

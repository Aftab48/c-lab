#include <stdio.h>

void rotate(int arr[], int n, int d) {
    d = d % n;
    int temp[d];
    // Copy first d elements to temp
    for (int i = 0; i < d; i++)
        temp[i] = arr[i];
    // Shift remaining elements to the left
    for (int i = d; i < n; i++)
        arr[i - d] = arr[i];
    // Copy temp elements to end
    for (int i = 0; i < d; i++)
        arr[n - d + i] = temp[i];
}

int main() {
    int n,i,d;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number of positions to rotate the array from: ");
    scanf("%d", &d);
    

    rotate(arr, n, d);

    printf("Rotated array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
/*
 * Question 4: Write an algorithm to rotate an array by a given number of positions.
 */

#include <stdio.h>

// Function to reverse array from start to end
void reverse(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// Function to rotate array left by d positions
void rotateLeft(int arr[], int n, int d) {
    d = d % n; // Handle cases where d > n
    if (d == 0) return;
    
    // Reverse first d elements
    reverse(arr, 0, d - 1);
    // Reverse remaining elements
    reverse(arr, d, n - 1);
    // Reverse entire array
    reverse(arr, 0, n - 1);
}

// Function to rotate array right by d positions
void rotateRight(int arr[], int n, int d) {
    d = d % n; // Handle cases where d > n
    if (d == 0) return;
    
    // Reverse last d elements
    reverse(arr, n - d, n - 1);
    // Reverse first n-d elements
    reverse(arr, 0, n - d - 1);
    // Reverse entire array
    reverse(arr, 0, n - 1);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n, d, direction;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter number of positions to rotate: ");
    scanf("%d", &d);
    
    printf("Enter direction (1 for left, 2 for right): ");
    scanf("%d", &direction);
    
    printf("Original array: ");
    printArray(arr, n);
    
    if (direction == 1) {
        rotateLeft(arr, n, d);
        printf("Array after left rotation by %d positions: ", d);
    } else {
        rotateRight(arr, n, d);
        printf("Array after right rotation by %d positions: ", d);
    }
    printArray(arr, n);
    
    return 0;
}


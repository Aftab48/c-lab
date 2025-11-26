/*
 * Question 6: Write a function to remove duplicates from a sorted array.
 */

#include <stdio.h>

int removeDuplicates(int arr[], int n) {
    if (n == 0 || n == 1) {
        return n;
    }
    
    int j = 0; // Index for unique elements
    
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    
    // Include the last element
    arr[j++] = arr[n - 1];
    
    return j; // Return new size
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements (sorted array): ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d sorted elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Original array: ");
    printArray(arr, n);
    
    int newSize = removeDuplicates(arr, n);
    
    printf("Array after removing duplicates: ");
    printArray(arr, newSize);
    printf("New size: %d\n", newSize);
    
    return 0;
}


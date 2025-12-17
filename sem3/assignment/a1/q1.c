/*
 * Question 1: Write a program to find the maximum element in an array.
 */

#include <stdio.h>
#include <limits.h>

int findMax(int arr[], int n) {
    if (n <= 0) {
        printf("Array is empty\n");
        return INT_MIN;
    }
    
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Array is empty\n");
        return 0;
    }
    
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int max = findMax(arr, n);
    printf("Maximum element in the array: %d\n", max);
    
    return 0;
}


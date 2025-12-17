/*
 * Question 5: Implement an algorithm to find the missing number in an array of integers from 1 to N.
 */

#include <stdio.h>

// Method 1: Using sum formula
int findMissingNumberSum(int arr[], int n) {
    // Expected sum of numbers from 1 to n+1
    long long expectedSum = (long long)(n + 1) * (n + 2) / 2;
    
    // Actual sum of array elements
    long long actualSum = 0;
    for (int i = 0; i < n; i++) {
        actualSum += arr[i];
    }
    
    return (int)(expectedSum - actualSum);
}

// Method 2: Using XOR
int findMissingNumberXOR(int arr[], int n) {
    int xor1 = 0; // XOR of all numbers from 1 to n+1
    int xor2 = 0; // XOR of all array elements
    
    for (int i = 1; i <= n + 1; i++) {
        xor1 ^= i;
    }
    
    for (int i = 0; i < n; i++) {
        xor2 ^= arr[i];
    }
    
    return xor1 ^ xor2;
}

int main() {
    int n;
    printf("Enter the number of elements (array should contain numbers from 1 to n+1 with one missing): ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d elements (one number from 1 to %d is missing): ", n, n + 1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int missing1 = findMissingNumberSum(arr, n);
    int missing2 = findMissingNumberXOR(arr, n);
    
    printf("Missing number (using sum method): %d\n", missing1);
    printf("Missing number (using XOR method): %d\n", missing2);
    
    return 0;
}


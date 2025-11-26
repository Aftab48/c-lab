/*
 * Question 9: Write a function to find the contiguous subarray with the largest sum (Kadane's algorithm).
 */

#include <stdio.h>
#include <limits.h>

// Kadane's Algorithm - O(n) time complexity
int maxSubarraySum(int arr[], int n) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    int start = 0, end = 0, s = 0;
    
    for (int i = 0; i < n; i++) {
        maxEndingHere += arr[i];
        
        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
            start = s;
            end = i;
        }
        
        if (maxEndingHere < 0) {
            maxEndingHere = 0;
            s = i + 1;
        }
    }
    
    printf("Maximum sum: %d\n", maxSoFar);
    printf("Subarray indices: %d to %d\n", start, end);
    printf("Subarray elements: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return maxSoFar;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("\n");
    maxSubarraySum(arr, n);
    
    return 0;
}


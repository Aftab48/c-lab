/*
 * Question 8: Create a program to find the longest subarray with a sum less than or equal to a given value.
 */

#include <stdio.h>
#include <limits.h>

void findLongestSubarray(int arr[], int n, int target) {
    int maxLength = 0;
    int startIndex = -1;
    int endIndex = -1;
    
    for (int i = 0; i < n; i++) {
        int currentSum = 0;
        
        for (int j = i; j < n; j++) {
            currentSum += arr[j];
            
            if (currentSum <= target) {
                int length = j - i + 1;
                if (length > maxLength) {
                    maxLength = length;
                    startIndex = i;
                    endIndex = j;
                }
            }
            // Continue even if currentSum > target because subsequent negative numbers might reduce the sum
        }
    }
    
    if (maxLength > 0) {
        printf("Longest subarray with sum <= %d:\n", target);
        printf("Length: %d\n", maxLength);
        printf("Indices: %d to %d\n", startIndex, endIndex);
        printf("Elements: ");
        for (int i = startIndex; i <= endIndex; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("No subarray found with sum <= %d\n", target);
    }
}

int main() {
    int n, target;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the target sum: ");
    scanf("%d", &target);
    
    findLongestSubarray(arr, n, target);
    
    return 0;
}


/*
 * Question 7: Implement an algorithm to find the majority element in an array.
 * (A majority element is an element that appears more than n/2 times)
 */

#include <stdio.h>

// Using Moore's Voting Algorithm 
int findMajorityElement(int arr[], int n) {
    // Step 1: Find candidate
    int candidate = arr[0];
    int count = 1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] == candidate) {
            count++;
        } else {
            count--;
        }
        
        if (count == 0) {
            candidate = arr[i];
            count = 1;
        }
    }
    
    // Step 2: Verify if candidate is majority
    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate) {
            count++;
        }
    }
    
    if (count > n / 2) {
        return candidate;
    }
    
    return -1; // No majority element
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
    
    int majority = findMajorityElement(arr, n);
    
    if (majority != -1) {
        printf("Majority element: %d\n", majority);
    } else {
        printf("No majority element found\n");
    }
    
    return 0;
}


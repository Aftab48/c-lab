/*
 * Question 3: Create a program to find the intersection of two arrays.
 */

#include <stdio.h>
#include <stdlib.h>

void findIntersection(int arr1[], int n1, int arr2[], int n2) {
    printf("Intersection: ");
    int found = 0;
    
    // For each element in arr1, check if it exists in arr2
    for (int i = 0; i < n1; i++) {
        // Check if this element was already printed
        int alreadyPrinted = 0;
        for (int k = 0; k < i; k++) {
            if (arr1[k] == arr1[i]) {
                alreadyPrinted = 1;
                break;
            }
        }
        
        if (alreadyPrinted) continue;
        
        // Check if arr1[i] exists in arr2
        for (int j = 0; j < n2; j++) {
            if (arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
                found = 1;
                break;
            }
        }
    }
    
    if (!found) {
        printf("No common elements");
    }
    printf("\n");
}

int main() {
    int n1, n2;
    
    printf("Enter size of first array: ");
    scanf("%d", &n1);
    int arr1[n1];
    printf("Enter %d elements for first array: ", n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &arr1[i]);
    }
    
    printf("Enter size of second array: ");
    scanf("%d", &n2);
    int arr2[n2];
    printf("Enter %d elements for second array: ", n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &arr2[i]);
    }
    
    findIntersection(arr1, n1, arr2, n2);
    
    return 0;
}


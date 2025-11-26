#include <stdio.h>

int findMajorityElement(int arr[], int n) {
    int candidate = -1, count = 0;
    
    for (int i = 0; i < n; i++) {
        if (count == 0) {
            candidate = arr[i];
            count = 1;
        } else if (arr[i] == candidate) {
            count++;
        } else {
            count--;
        }
    }

    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate)
            count++;
    }
    if (count > n / 2)
        return candidate;
    else
        return -1;
}

int main() {
    int n, i, majority;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    majority = findMajorityElement(arr, n);
    if (majority != -1)
        printf("Majority element is %d\n", majority);
    else
        printf("No majority element found\n");
    return 0;
}
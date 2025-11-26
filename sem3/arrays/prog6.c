#include <stdio.h>

int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (arr[j] != arr[i]) {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1;
}

int main() {
    int n,i,newLen;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    newLen = removeDuplicates(arr, n);

    printf("Array after removing duplicates:\n");
    for (i = 0; i < newLen; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
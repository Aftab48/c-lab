#include <stdio.h>

int main() {
    int n, k;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter array elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the maximum allowed sum: ");
    scanf("%d", &k);

    int maxLen = 0, start = 0, end = 0, sum = 0, tempStart = 0;

    for(int i = 0; i < n; i++) {
        sum += arr[i];
        while(sum > k && tempStart <= i) {
            sum -= arr[tempStart];
            tempStart++;
        }
        if(i - tempStart + 1 > maxLen) {
            maxLen = i - tempStart + 1;
            start = tempStart;
            end = i;
        }
    }

    printf("Longest subarray with sum <= %d is of length %d:\n", k, maxLen);
    for(int i = start; i <= end; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
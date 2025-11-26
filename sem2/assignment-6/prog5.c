#include <stdio.h>
int main(){
	int i,n,j, max = 0;
	printf("Enter the number of elements : ");
	scanf("%d", &n);
	int arr[n];
	printf("Enter the elements : ");
	
	for(i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	
	printf("The Array : ");
	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	
	for(i = 0; i < n; i++){
		for(j = 0; j < n-1-i; j++){
			if(arr[j] > arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	printf("The sorted Array: ");
	for(i = 0; i < n ; i++)
		printf("%d ", arr[i]);
	printf("\n");
			
	
}

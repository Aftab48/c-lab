#include <stdio.h>
int main(){
	int i,n, max = 0;
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
	
	int pos;
	printf("Enter the position for the element to be deleted : ");
	scanf("%d", &pos);
	
	for(i = pos-1; i<n-1;i++)
		arr[i] = arr[i+1];
	
	printf("The Array after deletion: ");
	for(i = 0; i < n-1 ; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

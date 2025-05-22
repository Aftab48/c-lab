#include <stdio.h>
int main(){
	int n, max = 0;
	printf("Enter the number of elements : ");
	scanf("%d", &n);
	int arr[n];
	printf("Enter the elements : ");
	
	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
		
	for(int i = 0; i < n; i++){
		if(arr[i] > max) max = arr[i];
	}
	printf("Max : %d\n", max);
}

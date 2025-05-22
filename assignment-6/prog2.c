#include <stdio.h>
int main(){
	int i,n, max = 0;
	printf("Enter the number of elements : ");
	scanf("%d", &n);
	int arr[n+1];
	printf("Enter the elements : ");
	
	for(i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	
	printf("The Array : ");
	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	
	int el,pos;
	printf("Enter the element and the position for the element to be inserted : ");
	scanf("%d %d", &el, &pos);
	
	i = n;
	while(i-- >= pos)
		arr[i+1] = arr[i];
		
	arr[i+1] = el;
	
	printf("The Array after insertion: ");
	for(i = 0; i <=n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

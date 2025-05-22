#include <stdio.h>
int main(){
	int i,n,j,m;
	printf("Enter the number of rows and columns : ");
	scanf("%d %d", &m,&n);
	int arr[m][n];
	int arr2[m][n];
	
	printf("Enter the elements of array1 : ");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			scanf("%d", &arr[i][j]);
	}
	
	printf("The first Array : \n");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	
	printf("Enter the elements of array2 : ");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			scanf("%d", &arr2[i][j]);
	}
	
	printf("The second Array : \n");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	
	int sum[m][n];
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			sum[i][j] = arr[i][j] + arr2[i][j];
	}
	
	printf("The final Array : \n");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			printf("%d ", sum[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

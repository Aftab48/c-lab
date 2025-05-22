#include <stdio.h>
int main(){
	int i,n,j,m;
	printf("Enter the number of rows and columns : ");
	scanf("%d %d", &m,&n);
	int arr[m][n];
	printf("Enter the elements : ");
	
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			scanf("%d", &arr[i][j]);
	}
	
	printf("The Array : \n");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

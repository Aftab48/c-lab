#include <stdio.h>
#include <string.h>

struct Student{
	char name[50];
	int roll;
	int marks;
};

int main(){
	struct Student students[3];
	int i, maxI=0;
	
	for(i = 0; i < 3; i++){
		printf("Enter details for student %d :\n", i+1);
		printf("Name : ");
		scanf("%[^\n]", students[i].name);
		printf("Roll No. :");
		scanf("%d", &students[i].roll);
		printf("Total Marks : ");
		scanf("%d", &students[i].marks);
		getchar();
	}
	
	for(i = 0; i < 3; i++){
		if(students[i].marks > students[maxI].marks) maxI = i;
	}
	
	printf("\nStudent with the highest marks:\n");
	printf("Name : %s\n", students[maxI].name);
	printf("Roll No. : %d\n", students[maxI].roll);
	printf("Total Marks : %d\n", students[maxI].marks);
}

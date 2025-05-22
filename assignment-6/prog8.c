#include <stdio.h>

struct Point{
	int x;
	int y;
};

int main(){
	struct Point p1 = {3,4};
	struct Point p2;
	
	printf("Enter the coordinates of the 2nd point : ");
	scanf("%d %d", &p2.x, &p2.y);
	
	printf("First Point : (%d,%d)\n", p1.x,p1.y);
	printf("Second Point : (%d,%d)\n", p2.x,p2.y);
}

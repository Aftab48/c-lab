#include <stdio.h>

struct Complex{
	float real;
	float img;
};

struct Complex add(struct Complex a, struct Complex b){
	struct Complex result;
	result.real = a.real + b.real;
	result.img = a.img + b.img;
	
	return result;
}

int main(){
	struct Complex c1,c2,sum;
	
	printf("Enter real and imaginary part of first complex number : ");
	scanf("%f %f", &c1.real, &c1.img);
	
	printf("Enter real and imaginary part of second complex number : ");
	scanf("%f %f", &c2.real, &c2.img);
	
	sum = add(c1,c2);
	
	printf("Sum = %.2f + %.2fi\n", sum.real, sum.img);
}

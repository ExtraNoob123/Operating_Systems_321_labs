#include <stdio.h>

int sum(int a, int b);


int main() {
	int a = 20;
	int b = 30;
	int result;
	
	result = sum (a, b);
	
	printf("Sum of a and b is: %d\n", result); 
	
	return 0;
}

int sum(int a, int b){
	int result;
	
	result = a + b;
	
	return result;
}

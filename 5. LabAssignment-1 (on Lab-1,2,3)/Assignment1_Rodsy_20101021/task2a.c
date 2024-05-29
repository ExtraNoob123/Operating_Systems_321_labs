#include <stdio.h>

int main() {
	int n1, n2;
	
	printf("Enter two numbers: ");
	scanf("%d %d", &n1, &n2);
	
	if (n1 > n2) {
		printf("Result: %d\n", n1 - n2);
	} 
	else if (n1 < n2) {
		printf("Result: %d\n", n1 + n2);
	}
	else {
		printf("Result: %d\n", n1 * n2);
	}
	
	return 0;
}
	

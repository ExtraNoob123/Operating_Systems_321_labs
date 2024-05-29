#include <stdio.h>

int main(){
	int a, b, c;
	a =10;
	b = 20;
	c = 30;
	if (a>b && b>c) {
		printf("The largest value is %d\n", a);
	}
	else if (a<b && b>c) {
		printf("The largest value is %d\n", b);
	} 
	else {
		printf("The largest value is %d\n", c);
	}
}

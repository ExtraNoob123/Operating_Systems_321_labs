#include <stdio.h>

int main(){
	int a = 1;
	
	
	while (a < 10) {
		int b = a%2;
		if (b == 0){
			printf("The even numbers are %d\n" , a);
		}
		a = a + 1;
	}
	
}

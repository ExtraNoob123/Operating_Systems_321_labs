#include <stdio.h>

int main(){
	char s[100];
	scanf("%s", s);
	
	char c;	
	c = getchar();
	
	int i =0;
	
	int count1 = 0;
	for (i in s){
		if (i in c){
			count1 = count1 + 1;
		}
	}	
	 
	
	printf("Number of  %d\n", count1);
	


	int count2 = 0;
	for (i in c){
		count2 = count2 + 1;
	}	
	 
	printf("c = %d\n", count2);
	
	return 0;
}


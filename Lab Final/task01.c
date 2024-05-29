#include <stdio.h>
#include <string.h>

void sortString(char str[]) {
	int count[2] = {0};
	int len = strlen(str);
	
	for (int i = 0; i < len; i++) {
		count[str[i] - '0']++;
	}
	
	int index =0;
	for (int i = 0; i <= 1; i++) {
		for (int j=0; j < count[i]; j++) {
			str[index++] = i + '0';
		}
	}
}

int main() {
	char str[100];
	printf("Enter a String of 0s and 1s: ");
	scanf("%s", str);
	
	sortString(str);
	
	printf("Sorted string: %s\n", str);
	return 0;
}

// Rodsy // 20101021

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void childProcess(int n) {
	printf("Child process: Square of odd integers up to %d:\n", n);
	for (int i =1; i <= n; i += 2) {
		printf("%d", i * i);
	}
	print("\n");
}

void grandchildProcess(int n) {
	printf("grandchild process: Cube of %d: %d\n", n, n*n*n);
}

int main() {
	int num;
	printf("Enter an integer: ");
	scanf("%d", &num);
	
	pid_t pid = fork();
	
	if (pid <0) {
		fprintf(stderr, "Fork failed\n");
		return 1;
	}else if (pid == 0) {
		if (num % 2 != 0) {
			childProcess(num);
		} else {
			pid_t gpid = fork();
			if (gpid < 0) {
				fprint (stderr, "Fork failed\n");
				return 1;
			} else if (gpid == 0) {
				grandchildProcess(num);
			} else {
				 wait(NULL);
			}
		} 
	} else {
		wait(NULL);
		printf("Parent process: End of the process\n");
	}
	return 0;
}

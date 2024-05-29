#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	
	pid_t id_child,id_grand;
	
	
	id_child = fork();
	
	if (id_child == 0){
		id_grand = fork();
		if (id_grand == 0){
			printf("I am grandchild\n");
		}
		else{
			id_grand = wait(NULL);
			printf("I am child\n");
		}
	}
	else{
		id_child = wait(NULL);
		printf("I am parent\n");
	}
	

}

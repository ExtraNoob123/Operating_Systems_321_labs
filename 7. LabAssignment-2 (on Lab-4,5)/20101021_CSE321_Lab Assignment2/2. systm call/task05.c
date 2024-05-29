#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int count=1;
int main(){
	
	pid_t id_child, id_grand1, id_grand2, id_grand3;
	
	id_child = fork();
	
	if (id_child == 0){
	
		count++;
		printf("%d.Child process ID:%d\n",count,getpid());
		
		id_grand1 = fork();
		count++;
		
		if (id_grand1 == 0){
			
			printf("%d.Grand Child process ID:%d\n",count,getpid());
			exit(0);
		}
		
		id_grand2 = fork();
		count++;
		
		if (id_grand2 == 0){
			
			printf("%d.Grand Child process ID:%d\n",count,getpid());
			exit(0);
		}
		
		id_grand3 = fork();
		count++;
		
		if (id_grand3 == 0){
			
			printf("%d.Grand Child process ID:%d\n",count,getpid());
			exit(0);
		}
		
		
	}
	else{
		printf("%d.Parent process ID:%d\n",count,getpid());
		wait(NULL);
	}
	
	

}

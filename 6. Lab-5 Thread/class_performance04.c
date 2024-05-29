#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	 FILE *parent_file, *child_file;
	 pid_t pid;
	 
	 parent_file =fopen("parent.txt", "w");
	 if (parent_file==NULL){
	 	fprintf(stderr,"Error creating parent.txt\n");
	 	exit(EXIT_FAILURE);
	 }
	 fprintf(parent_file, "This is the parent process.");
	 fclose(parent_file);
	 
	 pid=fork();
	 if (pid<0) {
	 	fprintf(stderr, "Fork failed\n");
	 	exit(EXIT_FAILURE);
	 }
	 else if  (pid == 0) {
	 	child_file = fopen("child.txt", "w");
	 if (child_file==NULL){
	 	fprintf(stderr,"Error creating child.txt\n");
	 	exit(EXIT_FAILURE);
	 }
	 fprintf(child_file, "This is the child process.");
	 fclose(child_file);
	 }
	 else {
	 	int status;
	 	waitpid(pid, &status, 0);
	 	printf("Contents of the parent.txt:\n");
	 	system("cat parent.txt");
	 }
	 return 0;
}


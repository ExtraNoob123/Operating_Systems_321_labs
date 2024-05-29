#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
	
	FILE *file ;
	char name[100];
	char input[100];
	
	if (argc != 2) {
		printf("Usage: %s <name>\n", argv[0]);
		return 1;
	}
	
	strcpy(name, argv[1]);
	
	file = fopen(name, "a");
	
	if(file == NULL){
		printf("File could not be opened or created.\n");
		return 1;
	}


	printf("Please enter '-1' to stop writing in the file\n");
	while (1) {
		printf("Enter a string: ");
		fgets(input,sizeof(input), stdin);
		
		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "-1") == 0) {
		    break;
		}

		fprintf(file, "%s\n", input);
	}
	
	fclose(file);
	
	printf("Strings written to file successfully./n");
	
	return 0;
}


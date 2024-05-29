#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char ch;
    int spaceFlag = 0;

    
    inputFile = fopen("input_2b.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

   
    outputFile = fopen("output_2b.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    
    while ((ch = fgetc(inputFile)) != EOF) {
        
        if (ch != ' ') {
            fputc(ch, outputFile);
            spaceFlag = 0;
        } else {

            if (spaceFlag == 0) {
                fputc(' ', outputFile);
                spaceFlag = 1; 
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Extra spaces removed. Check output.txt.\n");

    return 0;
}


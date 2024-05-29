#include <stdio.h>
#include <string.h>

int isPalindrome(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    
    while (start < end) {
        if (*start != *end) {
            return 0; //not
        }
        start++;
        end--;
    }
    
    return 1; //yes
}

int main() {
    char input[100];
    
    printf("Enter a string: ");
    scanf("%s", input);
    
    if (isPalindrome(input)) {
        printf("Palindrome\n");
    } else {
        printf("Not Palindrome\n");
    }
    
    return 0;
}


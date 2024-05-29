#include <stdio.h>
#include <string.h>

int isUpdated(char email[]) {
    char *domain = strstr(email, "@");
    
    if (domain != NULL) {
        if (strstr(domain, "kaaj.com") != NULL) {
            return 0; 
        }
    }
    
    return 1;
}

int main() {
    char email[100];
    
    printf("Enter email address: ");
    scanf("%s", email);
    
    if (isUpdated(email)) {
        printf("Email address is okay\n");
    } else {
        printf("Email address is outdated\n");
    }
    
    return 0;
}


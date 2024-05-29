#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[50];
    int lowercase = 0, uppercase = 0, digit = 0, special = 0;
    
    printf("Enter password: ");
    scanf("%s", password);
    
    for (int i = 0; i < strlen(password); i++) {
        if (islower(password[i])) {
            lowercase = 1;
        } else if (isupper(password[i])) {
            uppercase = 1;
        } else if (isdigit(password[i])) {
            digit = 1;
        } else if (password[i] == '_' || password[i] == ',' || password[i] == '$' || password[i] == '#' || password[i] == '@') {
            special = 1;
        }
    }
    
    if (lowercase && uppercase && digit && special) {
        printf("OK\n");
    } else {
        printf("%s%s%s%s\n",
               (lowercase ? "" : "Lowercase character missing, "),
               (uppercase ? "" : "Uppercase character missing, "),
               (digit ? "" : "Digit missing, "),
               (special ? "" : "Special character missing"));
    }
    
    return 0;
}


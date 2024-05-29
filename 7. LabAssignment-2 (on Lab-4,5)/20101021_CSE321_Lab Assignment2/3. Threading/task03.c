#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

int add_ascii(char *name) {
    int sum = 0, i = 0;
    while (name[i] != '\0') {
        sum = sum + name[i];
        i++;
    }
    return sum;
}

void *thread_function(void *arg) {

    char name[100];
    
    printf("Please enter your name:\n");
    scanf("%s", name);
    
    int add = add_ascii(name);
    int *add_ptr = malloc(sizeof(int));
    *add_ptr = add; 
    
    pthread_exit(add_ptr);
}

int main() {

    pthread_t thread_arr[3];
    int check[3];

    for (int i = 0; i < 3; i++) {
        pthread_create(&thread_arr[i], NULL, thread_function, NULL);
    }

    for (int i = 0; i < 3; i++) {
    
        int *result;
        
        pthread_join(thread_arr[i], (void **)&result); 
        check[i] = *result;
        free(result);
    }

    if (check[0] == check[1] && check[0] == check[2] && check[1] == check[2]) {
    
        printf("Youreka\n");
        
    } else if (check[0] == check[1] || check[0] == check[2] || check[1] == check[2]) {
    
        printf("Miracle\n");
        
    } else {
    
        printf("Hasta la vista\n");
        
    }

    return 0;
}


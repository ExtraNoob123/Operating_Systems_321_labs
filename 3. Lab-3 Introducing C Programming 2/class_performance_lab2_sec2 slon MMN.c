#include<stdio.h>

int main(){
    int i, j, n, value = 1, sum = 0;
    scanf("%d", &n);
    for(i=0; i<n; i++){
        for(j=0; j<i+1; j++){
            printf("%d ", value);
            sum = sum + value;
            value++;
        }
        printf("\n");
    }

    printf("Sum = %d\n", sum);
    printf("Address of sum = %p", &sum);
    return 0;
}
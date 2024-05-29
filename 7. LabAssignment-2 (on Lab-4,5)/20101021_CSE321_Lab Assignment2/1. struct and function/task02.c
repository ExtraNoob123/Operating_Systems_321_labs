#include <stdio.h>

void perfect_num_check(int start, int end){
    printf("Perfect numbers between %d and %d:\n", start, end);
    for (int i = start; i <= end; i++){
        int sum = 0;
        for(int j = 1; j <= i - 1; j++){
            if(i % j == 0){
                sum += j;
            }
        }
        if(sum == i){
            printf("%d\n",i);
        }
    }
}

int main(){
    int start, end;
    printf("Enter first number of range: ");
    scanf("%d", &start);
    printf("Enter second number of range: ");
    scanf("%d", &end);
    
    perfect_num_check(start, end);

    return 0;
}

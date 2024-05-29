#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int count=0;
void *thread_function(void *thread_id){
	
	count++;
	printf("thread-%d running\n",count);
	int thrd_id;
	
	for (int j=0; j<5; j++){
		sleep(0.002);
	}
	printf("thread-%d closed\n",count);	
	
}

int main(){
	
	pthread_t thread_arr[5];
	
	for (int i=0; i<5; i++){
		pthread_create(&thread_arr[i],NULL,thread_function,NULL);
		pthread_join(thread_arr[i],NULL);
	}

}


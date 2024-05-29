#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/shm.h>
#include <sys/ipc.h>

int main(){
	pid_t p_id;
	p_id=getpid();
	
	//explicit
	key_t key1;
	key1=123;
	printf("Key generated explicitly of process key1.c with id %d: %d\n",p_id,key1);
	
	//ftok() to generate key
	key_t key2;
	key2=ftok("/home/badrul/Desktop/IPC_Lab/Key_Gen",'m');
	if(key2==(key_t)-1){
		printf("error in ftok()\n");
	}
	printf("Key generated by ftok() of process key1.c with id %d: %d\n",p_id,key2);
	
	//System generated
	key_t key3;
	key3=IPC_PRIVATE;
	printf("Key generated by system of process key1.c with id %d: %d\n",p_id,key3);	


	return 0;
}

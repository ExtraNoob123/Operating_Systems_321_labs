// home class
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>  // wait funct er jonno

#define SHM_SIZE 100
#define BALANCE 1000

struct shared {
    char sel[100];
    int b;
};

int main() {
    int shmid;
    key_t key;
    struct shared *shm; // shm = shared memory
    char selection;
    int fd[2];
    char buffer[100];

    // pipe creation er jonno
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        exit(1); // = exit(EXIT_FAILURE) //1 = EXIT_FAILURE
    }

    // shared memory creation er jonno
    key = ftok(".", 's');
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // shared memory attach korar jonno
    shm = shmat(shmid, NULL, 0);
    if (shm == (struct shared *) -1) {
        perror("shmat");
        exit(1);
    }

    // user input prompt korar jonno
    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");
    scanf(" %c", &selection);

    // shared memory values set korar jonno
    shm -> b = BALANCE;
    shm -> sel[0] = selection;
    shm -> sel[1] = '\0';

    
    printf("Your selection: %c\n", selection); // to print user selection

    
    write(fd[1], shm, sizeof(struct shared));// to send data through pipe

    
    close(fd[1]);// pipe er write end close korte

    
    wait(NULL); // child process terminate howar jonno wait kora hochche

    // to read message from pipe
    read(fd[0], buffer, sizeof(buffer));
    printf("%s\n", buffer);

    
    shmdt(shm);// to detach shared memory

    
    shmctl(shmid, IPC_RMID, NULL);// to delete shared memory

    return 0;
}

// 20101021 // Rodsy

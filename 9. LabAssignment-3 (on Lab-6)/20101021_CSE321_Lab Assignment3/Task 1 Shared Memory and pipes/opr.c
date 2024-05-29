#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define SHM_SIZE 100

struct shared {
    char sel[100];
    int b;
};

int main() {
    int shmid;
    key_t key;
    struct shared *shm; // shm = shared memory
    int fd[2];
    char buffer[100];

    // pipe creation er jonno
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        exit(1); // = exit(EXIT_FAILURE) //1 = EXIT_FAILURE
    }



    // shared memory retrieve korte
    key = ftok(".", 's');
    shmid = shmget(key, SHM_SIZE, 0666);
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
    
    // to read message from pipe
    shm = (struct shared *)malloc(sizeof(struct shared)); // to allocate memory
    read(fd[0], shm, sizeof(struct shared));

    
    close(fd[0]);// pipe er read end close korte

    // user selection er basis e process korte
    switch (shm->sel[0]) {
        case 'a':
            if (shm->b > 0) {
                int amount;
                printf("Enter amount to be added:\n");
                scanf("%d", &amount);
                if (amount > 0) {
                    shm->b += amount;
                    printf("Balance added successfully\n");
                    printf("Updated balance after addition: %d\n", shm->b);
                } else {
                    printf("Adding failed, Invalid amount\n");
                }
            } else {
                printf("Adding failed, Invalid amount\n");
            }
            break;
        case 'w':
            if (shm->b > 0) {
                int amount;
                printf("Enter amount to be withdrawn:\n");
                scanf("%d", &amount);
                if (amount > 0 && amount <= shm->b) {
                    shm->b -= amount;
                    printf("Balance withdrawn successfully\n");
                    printf("Updated balance after withdrawal: %d\n", shm->b);
                } else {
                    printf("Withdrawal failed, Invalid amount\n");
                }
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
            break;
        case 'c':
            printf("Your current balance is: %d\n", shm->b);
            break;
        default:
            printf("Invalid selection\n");
    }
    // to write message to pipe
    write(fd[1], "Thank you for using", sizeof("Thank you for using"));

    // to detach shared memory
    shmdt(shm);
    free(shm); // allocated memory free korte

    return 0;
}

// 20101021 // Rodsy

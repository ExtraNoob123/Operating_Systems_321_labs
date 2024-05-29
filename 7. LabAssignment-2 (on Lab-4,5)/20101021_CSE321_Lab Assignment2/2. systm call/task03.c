#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t a = fork();
    pid_t b = fork();
    pid_t c = fork();

    int count = 1;

    if (a < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (a == 0) {

        if (getpid() % 2 != 0) {

            if (b < 0) {
                fprintf(stderr, "Fork failed\n");
                return 1;
            } else if (b == 0) {

                count = count + 1;
                exit(0);
            }
            count = count + 1;
        }
        exit(0);
    } else {

        wait(NULL);


        if (c < 0) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        } else if (c == 0) {

            if (getpid() % 2 != 0) {

                b = fork();
                if (b < 0) {
                    fprintf(stderr, "Fork failed\n");
                    return 1;
                } else if (b == 0) {

                    count = count + 1;
                    exit(0);
                }
                count = count + 1;
            }
            exit(0);
        } else {

            wait(NULL);
            count = count + 1;
            printf("Total processes created: %d\n", count);
            

        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_TEXT 512

// message er structure define korte
struct msg {
    long int type;
    char text[MAX_TEXT];
};

// ekta message send korar function
void send_message(int msqid, struct msg *message) {
    if (msgsnd(msqid, (void *)message, MAX_TEXT, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
}

// ekta message receive korar function
void receive_message(int msqid, struct msg *message, long int type) {
    if (msgrcv(msqid, (void *)message, MAX_TEXT, type, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
}

int main() {
    struct msg message;
    int msqid;
    key_t key;

    // ekta unique message queue er jonno create korte
    if ((key = ftok("msgqueue.txt", 'B')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // message queue create korte
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // otp generator er jonno fork process
    pid_t otp_pid = fork();

    if (otp_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (otp_pid == 0) {
        // Child process => otp_generator
        // login theke message read korte
        receive_message(msqid, &message, 1);
        printf("OTP generator received workspace name from log in: %s\n", message.text);

        // OTP generate korte (process id use kore)
        snprintf(message.text, MAX_TEXT, "%d", getpid());
        message.type = 2;
        send_message(msqid, &message);
        printf("OTP sent to log in from OTP generator: %s\n", message.text);

        // mail e OTP send korte
        message.type = 3;
        send_message(msqid, &message);
        printf("OTP sent to mail from OTP generator: %s\n", message.text);

        exit(EXIT_SUCCESS);
    }
    else {
        // Parent process => login
        printf("Please enter the workspace name: ");
        fflush(stdout);
        scanf("%s", message.text);

        if (strcmp(message.text, "cse321") != 0) {
            printf("Invalid workspace name\n");
            // message queue remove korar jonno
            msgctl(msqid, IPC_RMID, NULL);
            exit(EXIT_SUCCESS);
        }

        // otp_generator er kache workspace name send korte
        message.type = 1;
        send_message(msqid, &message);
        printf("Workspace name sent to otp generator from log in: %s\n", message.text);

        // mail theke OTP read korte
        receive_message(msqid, &message, 3);
        printf("Mail received OTP from OTP generator: %s\n", message.text);

        // OTP sent to login from mail
        message.type = 4;
        send_message(msqid, &message);
        printf("OTP sent to login from mail: %s\n", message.text);

        // Receive OTP from mail
        receive_message(msqid, &message, 4);
        printf("Log in received OTP from mail: %s\n", message.text);

        // otp_generator er theke OTP read korte
        receive_message(msqid, &message, 2);
        printf("Log in received OTP from OTP generator: %s\n", message.text);
    
        // mail theke received OTP ekta different variable store korte
        char mail_otp[MAX_TEXT];
        strcpy(mail_otp, message.text);
    
        // OTP guloke verify korte
        if (strcmp(message.text, mail_otp) == 0) {
            printf("OTP Verified\n");
        } else {
            printf("OTP Incorrect\n");
        }

        // message queue remove korte
        msgctl(msqid, IPC_RMID, NULL);
    }

    return 0;
}

// 20101021 // Rodsy

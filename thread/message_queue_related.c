#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_KEY 1234

// Define message structure
struct msg_buffer {
    long msg_type;          // Must be > 0
    char msg_text[100];
};

int main() {
    int msgid;
    struct msg_buffer message;

    // Create message queue
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // ---------- Child Process ----------
        message.msg_type = 1;  // Set message type
        strcpy(message.msg_text, "Hello from child!");

        // Send message to queue
        if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Child: Message sent.\n");
    } else {
        // ---------- Parent Process ----------
        sleep(1);  // Ensure child sends the message first

        // Receive message from queue
        if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Parent: Received message: %s\n", message.msg_text);

        // Cleanup: Delete the message queue
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(1);
        }
    }

    return 0;
}

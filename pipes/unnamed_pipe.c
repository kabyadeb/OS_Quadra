#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char message[] = "Hello from parent!";
    char buffer[100];

    pipe(fd); // Create unnamed pipe
    // fd[1] is for writing

// fd[0] is for reading

// Usually used for parent-child communication via fork().
    if (fork() == 0) {
        // Child process: Read
        close(fd[1]); // Close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
    } else {
        // Parent process: Write
        close(fd[0]); // Close read end
        write(fd[1], message, strlen(message));
    }

    return 0;
}

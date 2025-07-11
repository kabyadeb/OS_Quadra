#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>

int main() {
    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        // Parent process
        printf("Parent process (PID: %d) is exiting.\n", getpid());
        exit(0); // Parent exits immediately
    } else {
        // Child process
        sleep(5); // Sleep to ensure parent has exited
        printf("Child process (PID: %d, Parent PID: %d) is now orphan.\n", getpid(), getppid());
    }

    return 0;
}

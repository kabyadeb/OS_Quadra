#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is exiting.\n", getpid());
        exit(0); // Exits immediately, becomes zombie until parent collects status
    } else {
        // Parent process
        printf("Parent process (PID: %d) is sleeping.\n", getpid());
        sleep(10); // Sleep to keep parent alive, so child becomes zombie
        printf("Parent process is now exiting without wait().\n");
    }

    return 0;
}

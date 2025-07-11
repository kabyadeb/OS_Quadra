// Global variables are stored in the data segment.

// Local variables are stored on the stack.

// After fork(), the child process gets a copy of the parent’s memory.

// So, changes in the child do not affect the parent, and vice versa.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int global_var = 100; // Global variable

int main() {
    int local_var = 50; // Local variable

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        global_var += 10;
        local_var += 10;
        printf("Child Process:\n");
        printf("  PID: %d\n", getpid());
        printf("  Global Variable: %d\n", global_var);
        printf("  Local Variable: %d\n\n", local_var);
    } else {
        // Parent process
        sleep(1); // Ensure child runs first for clarity
        printf("Parent Process:\n");
        printf("  PID: %d\n", getpid());
        printf("  Global Variable: %d\n", global_var);
        printf("  Local Variable: %d\n", local_var);
    }

    return 0;
}

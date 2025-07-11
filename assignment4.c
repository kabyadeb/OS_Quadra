#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int a = 10, b = 39;
    pid_t pid;
     printf("Parent process (PID: %d) starting. Parent PID:%d\n", getpid(),getppid());

    for (int i = 0; i < 3; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0) {
            // Child process
            printf("Child %d (PID: %d) started.\n", i + 1, getpid());
            sleep(20);

            if (i == 0)
                printf("Child 1: %d + %d = %d\n", a, b, a + b);
            else if (i == 1)
                printf("Child 2: %d - %d = %d\n", a, b, a - b);
            else
                printf("Child 3: %d * %d = %d\n", a, b, a * b);

            exit(0); // Exit child
        }
        // Parent continues loop to fork next child
    }

    // Parent waits for all 3 children
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent process (PID: %d) finished waiting.\n", getpid());
    return 0;
}

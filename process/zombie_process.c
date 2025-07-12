#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child [%d] running... then exiting.\n", getpid());
        exit(0);  // Child exits immediately — becomes zombie if not waited on
    }
    else {
        // Parent process does NOT call wait()
        printf("Parent [%d] sleeping for 30 seconds. Child: %d\n", getpid(), pid);
        sleep(30);  // During this time, the child is a zombie
        printf("Parent exiting now.\n");
    }

    return 0;
}


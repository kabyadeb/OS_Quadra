#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/prctl.h>
#include<sys/wait.h>

#define _GNU_SOURCE

int main() {
    int a = 10, b = 39;
    pid_t pid1, pid2, pid3;

    printf("Parent PID: %d\n", getppid());

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed for child 1");
        return 1;
    } else if (pid1 == 0) {
        // Inside child 1
        prctl(PR_SET_NAME, (unsigned long)"child_1", 0, 0, 0);
        char name[16];
        prctl(PR_GET_NAME, name);
        printf("Process running as: %s (PID: %d, PPID: %d)\n", name, getpid(), getppid());
        sleep(15);
        return 0;
    }

    // Only parent continues to fork
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed for child 2");
        return 1;
    } else if (pid2 == 0) {
        prctl(PR_SET_NAME, (unsigned long)"child_2", 0, 0, 0);
        char name[16];
        prctl(PR_GET_NAME, name);
        printf("Process running as: %s (PID: %d, PPID: %d)\n", name, getpid(), getppid());
        sleep(15);
        return 0;
    }

    pid3 = fork();
    if (pid3 < 0) {
        perror("Fork failed for child 3");
        return 1;
    } else if (pid3 == 0) {
        prctl(PR_SET_NAME, (unsigned long)"child_3", 0, 0, 0);
        char name[16];
        prctl(PR_GET_NAME, name);
        printf("Process running as: %s (PID: %d, PPID: %d)\n", name, getpid(), getppid());
        sleep(15);
        return 0;
    }

    // Parent waits for all children
    prctl(PR_SET_NAME, (unsigned long)"parent_process", 0, 0, 0);
    char name[16];
    prctl(PR_GET_NAME, name);
    printf("Process running as: %s (PID: %d, PPID: %d)\n", name, getpid(), getppid());
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent process (PID: %d) finished waiting.\n", getpid());
    return 0;
}

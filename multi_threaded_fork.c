#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

void* thread_func(void* arg) {
    printf("Thread %ld running in process %d\n", (long)arg, getpid());
    sleep(2);  // Allow main thread to fork while this runs
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create two threads
    pthread_create(&t1, NULL, thread_func, (void*)1);
    pthread_create(&t2, NULL, thread_func, (void*)2);

    sleep(1);  // Ensure threads are running

    printf("\n[Main thread] Forking process now (PID = %d)\n", getpid());

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("[Child] After fork(), PID = %d, PPID = %d\n", getpid(), getppid());
        printf("[Child] Sleeping for 2 seconds...\n");
        sleep(2);

        printf("[Child] Calling exec() now...\n");
        execlp("echo", "echo", ">>> This is the new program after exec!", NULL);

        // If exec fails
        perror("exec");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        printf("[Parent] Waiting for child (PID = %d)...\n", pid);
        wait(NULL);
        printf("[Parent] Child finished.\n");
    } else {
        perror("fork");
        exit(1);
    }

    // Join threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("[Main thread] Exiting main process.\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

#define SHM_KEY 0x1234

int main() {
    int shmid;
    int *counter;

    // Create shared memory segment of size int
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory to this process
    counter = (int *) shmat(shmid, NULL, 0);
    if (counter == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    *counter = 0;  // Initialize shared counter

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    int i;
    if (pid == 0) {
        // Child process: increment shared counter 100000 times
        for (i = 0; i < 10000; i++) {
            int temp = *counter;
            temp++;
            *counter = temp;
        }
        printf("Child done.\n");
    } else {
        // Parent process: increment shared counter 100000 times
        for (i = 0; i < 10000; i++) {
            int temp = *counter;
            temp++;
            *counter = temp;
        }

        // Wait for child
        wait(NULL);

        printf("Parent done. Final counter: %d\n", *counter);

        // Detach and remove shared memory
        shmdt(counter);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}

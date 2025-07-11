#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 12345

int main() {
    int shmid;
    int *counter;

    // Get existing shared memory
    shmid = shmget(SHM_KEY, sizeof(int), 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    counter = (int *) shmat(shmid, NULL, 0);
    if (counter == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    // Increment counter 1000 times
    for (int i = 0; i < 10; i++) {
        int temp = *counter;
        temp++;
        sleep(1); // slow down to expose race condition
        *counter = temp;
    }

    printf("Reader done. Final counter = %d\n", *counter);

    // Detach
    shmdt(counter);

    return 0;
}

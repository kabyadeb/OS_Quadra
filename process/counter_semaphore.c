#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_RESOURCES 3  // Semaphore count (e.g., 3 slots)
#define NUM_THREADS   5

sem_t sem;  // Counting semaphore

void* access_resource(void* arg) {
    int id = *((int*)arg);
    sem_wait(&sem);  // Decrease count (P operation)
    printf("Thread %d acquired resource\n", id);

    sleep(1);  // Simulate using the resource

    printf("Thread %d releasing resource\n", id);
    sem_post(&sem);  // Increase count (V operation)
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    sem_init(&sem, 0, MAX_RESOURCES);  // 0 = semaphore shared between threads

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, access_resource, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem);
    return 0;
}

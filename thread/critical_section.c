#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0; // 🟡 Global shared variable
// pthread_mutex_t lock;

void* increment() {
  printf("Thread running on CPU: %d\n", sched_getcpu());
    for (int i = 0; i < 1000000; i++) {
      // pthread_mutex_lock(&lock);
        counter++;  // 🔥 Critical section
        // usleep(100);
        // sleep(1);
        // pthread_mutex_unlock(&lock);
        printf("Thread1: %d\n",counter);
    }
    return NULL;
}

void* decrement() {
  printf("Thread running on CPU: %d\n", sched_getcpu());
    for (int i = 0; i < 1000000; i++) {
      // pthread_mutex_lock(&lock);
        counter--;  // 🔥 Critical section
        // usleep(100);
        // sleep(1);
        // pthread_mutex_unlock(&lock);
         printf("Thread 2: %d\n",counter);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, decrement, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final value of counter: %d\n", counter); 

    return 0;
}

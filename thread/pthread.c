#include <stdio.h>
#include <pthread.h>

void* print_message() {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t tid;
    // pthread_create(thread id,)
    // thread: pointer to a pthread_t variable to store the thread ID.
    // attr: thread attributes (can be NULL for default).
    // start_routine: the function the thread will run.
    // arg: argument to pass to that function.
    pthread_create(&tid, NULL, print_message, NULL);
    pthread_join(tid, NULL);
    // is used to wait for the thread with ID tid to finish execution
    return 0;
}

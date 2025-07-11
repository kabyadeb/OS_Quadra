#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <string.h>

int main() {
    prctl(PR_SET_NAME, (unsigned long)"child_1", 0, 0, 0);  // Set short name
    char name[16];
    prctl(PR_GET_NAME, name);
    printf("Process running as: %s (PID: %d)\n", name, getpid());

    sleep(10); // Sleep so you can inspect with `ps -e` or `htop`
    return 0;
}

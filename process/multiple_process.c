#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sched.h>  
#include <pthread.h>
#define _GNU_SOURCE 

int main(){

  for (int i=0;i<10;i++){
    pid_t pid;
    pid=fork();
    if(pid==-1){
    perror("Failed to create process");
    // Exit due to an error
    exit(1);
    }

    else if(pid==0){
    printf("I'm the child process\n");
    // getcpu()-> used to determine which CPU core
    printf("My Process ID %d and cpu core :%d\n",getpid(),sched_getcpu());
    sleep(10);
    // slow down for showing pstree -p shell_pid
    exit(0);
    }

    
  }

  for(int i=0;i<10;i++){
    wait(NULL);
  }
  
  printf("Parent Process ID: %d and cpu core: %d \n",getpid(),sched_getcpu());
  
  
  
  return 0;
}
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sched.h>  
#include <pthread.h>
#define _GNU_SOURCE 

int main(){

  /*
  Creates a new process by duplicating the calling process.
  The child is an exact copy of the parent (same code, data, heap, stack — initially).
  Both processes (parent and child) will continue execution independently from the line just after fork()
  pid> 0	Parent process	PID of the child
  pid=	Child process	Means "I am the child"
  pid=-1	Parent process	Fork failed (no child created)
  */
  pid_t pid1;
  pid1=fork();
  if(pid1==-1){
    perror("Failed to create process");
    // Exit due to an error
    exit(1);
  }
  else if(pid1==0){
    printf("I'm the child process\n");
    // getcpu()-> used to determine which CPU core
    printf("My Process ID %d and cpu core :%d\n",getpid(),sched_getcpu());
    sleep(10);
    // slow down for showing pstree -p shell_pid
  }
  else{
    printf("Parent Process ID: %d and cpu core: %d \n",getpid(),sched_getcpu());
    wait(NULL);
    
  }
  return 0;
}

// show how many process using pstree -p shell_pid
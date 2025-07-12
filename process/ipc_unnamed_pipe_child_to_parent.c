# include<stdio.h>
# include<unistd.h>
# include<string.h>
# include<sys/wait.h>
# include<stdlib.h>

int main(){
  /*
  *| Index   | Meaning                   |
  *| ------- | ------------------------- |
  *| `fd[0]` | **Read end** of the pipe  |
  *| `fd[1]` | **Write end** of the pipe |
  * Think of it like a one-way water pipe:
  * Water enters from one side (write end = fd[1])
  * Water comes out the other side (read end = fd[0])
  *
  */
  
  
  int fd[2];
  char message[]="Hey Parent I'm Your Child";
  char buffer[100];
  
  pipe(fd);
  
  if(fork()==0){
    close(fd[0]);
    write(fd[1],message,strlen(message)+1);
    printf("Child Sent to the parent\n");
    exit(0);
    }
  else{
    close(fd[1]);
    // sizeof(message) sends entire 100 bytes (including unused nulls)
    read(fd[0],buffer,sizeof(buffer));
    // This writes only the actual message plus the null terminator.
    printf("Parent Received: %s\n",buffer);
    wait(NULL);
    }
  
    return 0;
  }

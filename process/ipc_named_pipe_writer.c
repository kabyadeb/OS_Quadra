# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include<string.h>

int main(){
  /*
  * A named pipe (also called a FIFO, which stands for First In, First Out) is a special file that allows 
  * inter process communication (IPC) — like a regular pipe — but with a name in the filesystem.
  * mkfifo does not store data permanently.It only acts as a temporary communication channel for  
  * transferring data between processes.
  * mkfifo file_name
  * This file is of type FIFO (named pipe) 
  * When one process writes to the pipe:
  * The data goes into kernel memory, not the disk file.
  * When another process reads from it:
  * The data is pulled from the kernel buffer.
  * Once read, the data is gone — not saved.
  */
  char message[100];
  snprintf(message,sizeof(message),"Process id %d",getpid());
  int fd=open("pipe",O_WRONLY);
  write(fd,message,strlen(message)+1);
  close(fd);
  

  return 0;
}

/*
* | Constant     | Meaning                                       |
* | ------------ | --------------------------------------------- |
* | `O_RDONLY`   | Open for reading only                         |
* | `O_WRONLY`   | Open for writing only                         |
* | `O_RDWR`     | Open for reading and writing                  |
* | `O_CREAT`    | Create the file if it doesn’t exist           |
* | `O_EXCL`     | Fail if the file exists (used with `O_CREAT`) |
* | `O_TRUNC`    | Truncate file to 0 length if it exists        |
* | `O_APPEND`   | Writes go to the end of the file              |
* | `O_NONBLOCK` | Non-blocking mode                             |

*/


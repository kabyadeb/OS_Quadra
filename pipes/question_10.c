// named_pipe_reader.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[100];

    if(fork()>0){
      int fd = open("name_pipe", O_WRONLY);
      char message[] = "Hello from writer!";
      write(fd, message, strlen(message) + 1);
      close(fd);
    }
    else{    
    int fd = open("name_pipe", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("Reader received: %s\n", buffer);
    close(fd);
    }

    return 0;
}

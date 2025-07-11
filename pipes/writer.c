// named_pipe_writer.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("name_pipe", O_WRONLY);
    char message[] = "Hello from writer!";
    write(fd, message, strlen(message) + 1);
    close(fd);
    return 0;
}

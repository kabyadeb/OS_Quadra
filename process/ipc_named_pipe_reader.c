# include <fcntl.h>
# include <unistd.h>
# include<string.h>
# include <stdio.h>
# include <unistd.h>

int main(){
  char buffer[100];
  int fd=open("pipe",O_RDONLY);
  read(fd,buffer,sizeof(buffer));
  printf("%s\n",buffer);
  printf("My Process ID %d\n",getpid());
  close(fd);

return 0;
}

# include <stdio.h>
# include <stdlib.h>
# include <sys/msg.h>
# include <sys/wait.h>
# include <string.h>
# define KEY 1234

struct msgbuffer{
  long mtype;
  char msg[1000];
};

int main (){
  struct msgbuffer buf;
  int id=msgget(KEY,0666|IPC_CREAT);
  if(id==-1){
    perror("Failed to create msg id");
    exit(1);
  }
  buf.mtype=1;
  strcpy(buf.msg,"Hey How Are You Reader?");
  msgsnd(id,&buf,sizeof(buf.msg),0);
  
  return 0;
}

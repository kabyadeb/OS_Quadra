# include <stdio.h>
# include <stdlib.h>
# include <sys/msg.h>
# include <sys/wait.h>
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
  msgrcv(id,&buf,sizeof(buf.msg),1,0);
  printf("Reader:%s\n",buf.msg);
  msgctl(id,IPC_RMID,NULL);
  return 0;

}

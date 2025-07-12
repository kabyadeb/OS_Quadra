#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
  key_t key =1234;
  int shmid=shmget(key,sizeof(int),0666|IPC_CREAT);

  int *cnt=(int *) shmat(shmid,NULL,0);

  if(shmid<0){
    perror("shmget");
    exit(1);
  }
  *cnt = 0;
  pid_t pid=fork();

  for(int i=0;i<10;i++){
    printf("%d\n",*cnt);
    (*cnt)+=1;
  }
  if(pid==0){
    shmdt(cnt);
    exit(0);
  }

  else{
    wait(NULL);
    printf("Final Counter Value: $%d",*cnt
    );
    shmdt(cnt);
    shmctl(shmid,IPC_RMID,NULL);
    // Delete shared memory
  }

  
  return 0;
}

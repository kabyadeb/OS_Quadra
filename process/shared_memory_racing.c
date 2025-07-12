# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/shm.h>
# include <unistd.h>

#define KEY 1234

int main(){
  
  int shmid=shmget(KEY,10,0666|IPC_CREAT);
  if(shmid==-1){
  perror("Failed to create shared memory");
  exit(1);
  }
  if(fork()==0){
    int *counter=(int *)shmat(shmid,NULL,0);
    for(int i=0;i<1000000;i++){
      (*counter)+=1;
    }
    shmdt(counter);
  }
  
  else{
    int * counter=(int *)shmat(shmid,NULL,0);
    *counter=10;
    for(int i=0;i<1000000;i++){
      (*counter)+=1;
    }
    wait(NULL);
    printf("Final Value: %d\n",(* counter));
    shmdt(counter);
    shmctl(shmid,IPC_RMID,NULL);
  }
  return 0;
  
}

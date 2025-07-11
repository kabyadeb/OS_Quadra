#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>

int a=10;

int main(){

  // int a=10,b=39;
  pid_t pid1,pid2,pid3;
  pid1=fork();
  if(pid1<0){
    perror("Fork failed for child 1");
  }
  else if(pid1==0){
    for(int i=0;i<100000000;i++){
      // printf("Child : %d",a);
      a+=1;
    }
    // printf("Processing By child 1: %d\n",a+b);
  }
  else{
    for(int i=0;i<10;i++){
      // printf("Child : %d",a);
      a+=1;
    }
    wait(NULL);
    printf("%d\n",a);

  }

  // pid2=fork();
  // if(pid2<0){
  //   perror("Fork failed for child 2\n");
  // }else if(pid2==0){
  //   printf("Processing by 2nd Process:%d\n",a-b);
  // }

  // pid3=fork();
  // if(pid3<0){
  //   perror("Fork failed for child 3\n");
  // }else if(pid3==0){
  //   printf("Processing by 3nd Process:%d\n",a*b);
  // }

  return 0;
}
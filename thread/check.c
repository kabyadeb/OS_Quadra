#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>

int main(){

  fork();
  printf("Bangladesh");
  fork();
  printf("Bangladesh");
  fork();
  return 0;
}
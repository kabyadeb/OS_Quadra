# include <stdio.h>
# include <pthread.h>
// race condtion between two threads
int counter=0;
void * increment(){
  
  for(int i=0;i<1000000;i++){
  counter+=1;
  }
  
}

void * decrement(){
  
  for(int i=0;i<1000000;i++){
  counter-=1;
  }
  
}
int main(){
  
  pthread_t pid1,pid2;
  
  pthread_create(&pid1,NULL,increment,NULL);
  pthread_create(&pid2,NULL,decrement,NULL);
  pthread_join(pid1,NULL);
  pthread_join(pid2,NULL);
  printf("Final Value :%d\n",counter);
  return 0;
}

/*
* pthread_create( pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg) 
* Creates a new thread
* pthread_t *thread ->Pointer to a variable that will store the thread ID 
* Pointer to a pthread_attr_t struct to set thread attributes (stack size, detach state, etc). Use NULL for default.
* The function to run in the new thread. It must take a void * as argument and return void *
* The argument passed to start_routine. Can be NULL or cast from any pointer type.

* 0	Success

*/

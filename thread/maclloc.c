# include<stdio.h>
# include <pthread.h>
#include <stdlib.h>

/*
malloc(sizeof(int)) asks the system to allocate enough memory to store one integer.
It returns a pointer (void*) to that memory.
The * operator dereferences the pointer.

This means "go to the memory location pointed to by result and store the value 10 there."
*/

int main(){
  int* result=malloc(sizeof(int));
  *result=10;
  printf("%d\n",*result);
  
  int a=10;
  int *p=&a;
  printf("%d",*p);
}

# include<stdio.h>
# include <pthread.h>
#include <stdlib.h>

// void * is a generic pointer — a pointer with no specific type.

void * find_max(void * args){
// args is expected to be a pointer to an array of pointers (void* arg[2]).
// Cast args to int** (pointer to pointer to int), so you can index it.
// ((int**)args)[0] fetches the first element of that array, which is a pointer to the integer array 
// you want to search.

  int *arr=((int **)args)[0]; // You know args points to an array of pointers to int (or to data).
  int n= *((int **)args)[1];
  int mx=0;
  for (int i=0;i<n;i++){
  if(mx<arr[i])mx=arr[i];
  }
  int* result=malloc(sizeof(int));
  *result=mx;
  return result;
}

int main(){
  pthread_t pid1,pid2,pid3;
  int n;
  printf("Enter Length Of Array: ");
  scanf("%d",&n);
  int arr[n];
  for(int i=0;i<n;i++){
  printf("Enter Number%d : ",i+1);
  scanf("%d",&arr[i]);
  }
  // Each element is a void *, meaning a generic pointer.
  void * arg[2];
  // arr[0] is array of pointer
  arg[0]=arr;
  arg[1]=&n;
  // It declares a pointer named
  void * max_number;
  pthread_create(&pid1,NULL,find_max,arg);
  // &max_number gives the address of the pointer variable itself
  pthread_join(pid1,&max_number);
  int max = *(int*)max_number;
  printf("Max value: %d\n", max);
  
  return 0;
}

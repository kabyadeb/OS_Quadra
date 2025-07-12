# include<stdio.h>
# include<unistd.h>
# include<sys/wait.h>
# include<sys/types.h>
# include<stdlib.h>
# include<sys/prctl.h>

int main(){
	/*
	 *prctl() stands for process control and is a Linux-specific system call that
	 allows a process to control specific characteristics or behaviors of itself
       	or its child processes
	*/
	/* 
	 * PR_SET_NAME (and PR_GET_NAME) for Set/Get process name visible in tools like ps or top
	 */

	for(int i=0;i<10;i++){
		pid_t pid=fork();
		if(pid==-1){
			perror("Failed to create process");
			exit(1);
		}
	
		else if(pid==0){
			char name [16];
			snprintf(name,sizeof(name),"process_%d",i);
			prctl(PR_SET_NAME,(unsigned long) name,0,0,0);
			printf("%s: %d\n",name,getpid());
			sleep(10);
			exit(0);	
		}
	
	}
	
	for(int i=0;i<10;i++){
		wait(NULL);
	}
		
	printf("Parent Process: %d\n",getpid());	
	return 0;
}

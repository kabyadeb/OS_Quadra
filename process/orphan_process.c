# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<sys/wait.h>


int main(){
	
	pid_t pid = fork();
	if(pid==-1){
		perror("Failded to create process \n");
		exit(1);
	}
	else if(pid==0){
		printf("child %d running...\n ",getpid());
		printf("parent %d\n ",getppid());
		sleep(5);
		printf("child process is terminated.parent Id:%d\n",getppid());
		exit(0);
	}

	else {
		printf("Main process terminated without child finished\n");
		exit(0);
	}

	return 0;
}

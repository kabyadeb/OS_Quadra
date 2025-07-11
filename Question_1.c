/*
    Write a C program to create a main process named ‘parent_process’ having 3 
    child processes without any grandchildren processes.  
 
    Trace parent and child processes in the process tree.   
 
    Show that child processes are doing addition, subtraction and multiplication 
    on two variables initialized in the parent_process

*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid_1 , pid_2, pid_3;
    int a = 20 , b = 10;

    pid_1 = fork(); // Creating new process

    if(pid_1 == 0){   // 1st Child Process

        printf("\nThis is the 1st child process with PID : %d and PPID: %d\n", getpid(), getppid());
        int add = a + b;
        printf("Addition of %d and %d is %d\n", a , b , add);
        sleep(10);
        printf("1st Child Process is terminating.\n\n");

    }else if(pid_1 > 0){ // Parent Process

        pid_2 = fork(); // Creating new Process

        if(pid_2 == 0){ // This is 2nd Child

            printf("\nThis is the 2st child process with PID : %d and PPID: %d\n", getpid(), getppid());
            int sub = a - b;
            printf("Subtraction of %d and %d is %d\n", a , b , sub);
            sleep(10);
            printf("2st Child Process is terminating.\n\n");

        }else if(pid_2 >0){ // Parent process

            pid_3 = fork();

            if(pid_3 == 0){ // This is 3rd Child

                printf("\nThis is the 3st child process with PID : %d and PPID: %d\n", getpid(), getppid());
                int mul = a * b;
                printf("Multiplication of %d and %d is %d\n", a , b , mul);
                sleep(10);
                printf("3st Child Process is terminating.\n\n");

            }else if(pid_3 > 0){
                // Wait for terminating Child Process
                wait(NULL);
                wait(NULL);
                wait(NULL);
                printf("Parent process completed.\n");
            }
        }
    }
}

/*
    gcc Question_1.c -o Question_1
    ./Question_1

    pstree -p | grep Question_1
*/
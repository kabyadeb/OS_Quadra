# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/msg.h>
# include <stdlib.h>
# include <sys/wait.h>

# define KEY 1234

struct msgbuf{
/* mtype is a long integer field at the start of every message you send using System V //message queues.It must be > 0. It represents the type or category of the message. Without setting mtype, your message is invalid — it could cause msgsnd() to fail or cause msgrcv() not to receive it.
msg.mtype = 1;  // status update
msg.mtype = 2;  // error message
msg.mtype = 3;  // data response
*/
long mtype;
char msg[100];
};

/*
* msgget() function is used to create or access a System V message queue.
* int msgget(key_t key, int msgflg);
* key	A unique integer key that identifies the message queue (like an ID).
* msgflg	Flags that control creation, permissions, and behavior.IPC_EXCL	Fail if 
* the queue already exists (used with IPC_CREAT). IPC_CREAT Create
* the queue if it doesn't exist.0666 (octal)	Permissions: read/write for owner, 
* group, others.
* msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
* msqid	The message queue identifier, obtained from msgget().
* msgp	Pointer to the message buffer (your struct) that holds the message to send.
* msgsz	Size of the message excluding the long mtype field (just the actual message data).
* msgflg	Flags controlling behavior 
* 0	Block if the queue is full.
* System V requires that your message buffer begins with a long mtype field
* ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
* msgtyp	The mtype you want to receive (or 0 to receive any)
* msgflg	Flags like 
*
* int msgctl(int msqid, int cmd, struct msqid_ds *buf); 
* msqid	The message queue ID returned by msgget()
* cmd	The command to perform on the queue
* buf	A pointer to a struct msqid_ds, used to get/set queue info
* IPC_RMID	Remove the message queue
* buf is not needed → pass NULL
*/

int main(){
  
  int msgid=msgget(KEY,0666|IPC_CREAT);
  
  if(msgid==-1){
  perror("Failed to create queue");
  exit(1);
  }
  if(fork()==0){
    struct msgbuf msg;
    msgrcv(msgid,&msg,sizeof(msg.msg),1,0);
    // 1	Filter: receive only mtype == 1
    // 0	Accept any message type
    printf("Child Received :%s\n",msg.msg);
    exit(0);
  }
  else{
  struct msgbuf msg;
   msg.mtype = 1;
   strcpy(msg.msg, "Hello from parent!");
   msgsnd(msgid,&msg,sizeof(msg.msg),0);
   wait(NULL);
   msgctl(msgid,IPC_RMID,NULL);
  }
  return 0;
}

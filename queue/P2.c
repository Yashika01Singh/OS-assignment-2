#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct my_msgbuf{
	long id;
	char message[5][10] ;
};
struct second{
	long id;
	int index;
};
int main (int argc , char *argv[]){
    //P2
    	 
	printf("P2 running \n");

	//Recieving message with queue
	struct my_msgbuf buf;
	int msqid , sendid , num;
	key_t key , sendkey;
	if((key = ftok("P1.c" , 'B' )) == -1 ||  (sendkey = ftok("P2.c" , 'C')) == -1  ) {
		perror("ftok");
		exit(1);
	}
	if((msqid = msgget (key , 0644 | IPC_CREAT  ) ) == -1 || (sendid = msgget(sendkey , 0644 |IPC_CREAT)) ==-1 )  {
		perror("msgget");
		exit(1);
	}
	struct second buf2;
	for(;;){
		buf2.id = 2;

		if(num = msgrcv(msqid , &buf , sizeof( buf.message) , 0,0) == -1)
		{perror("msgrcv");
			printf("%dkkkkk \n", num) ; 
		exit(1);}
		if(strcmp(buf.message[0] , "end" ) == 0) {
			
			return 0;}
		for(int i=0 ; i<5 ; i++)
		printf("recieved %s  at index %c %c \n " , buf.message[i] , buf.message[i][5] , buf.message[i][6]);
		buf2.index =  10*(buf.message[4][5] - '0' ) + buf.message[4][6] - '0' ;
		if(msgsnd(sendid , &buf2 , sizeof(buf2.index) , 0) ==-1) {
			perror("msgsnd");}
	}

	return 0;
}

	


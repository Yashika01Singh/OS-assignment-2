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
	int msqid , sendid;
	key_t key , sendkey;
	if((key = ftok("P1.c" , 'B' )) == -1 ||  (sendkey = ftok("P2.c" , 'C')) == -1  ) {
		perror("ftok");
		exit(1);
	}
	if((msqid = msgget (key , 0644  ) ) == -1 || (sendid = msgget(sendkey , 0644)) ==-1 )  {
		perror("msgget");
		exit(1);
	}
	struct second buf2;
	for(;;){
		buf2.id = 2;

		if(msgrcv(msqid , &buf , sizeof( buf.message) , 0,0) == -1)
		{perror("msgrcv");
		exit(1);}
		for(int i=0 ; i<5 ; i++)
		printf("spock %s  at index %c %c \n " , buf.message[i] , buf.message[i][5] , buf.message[i][6]);
		buf2.index =  10*(buf.message[4][5] - '0' ) + buf.message[4][6] - '0' ;
		if(msgsnd(sendid , &buf2 , sizeof(buf2.index) , 0) ==-1) {
			perror("msgsnd");}
	}
	printf("P2 finished\n");
	return 0;
}

	
/*

   for(int i=0 ; i<50 ; i++)
       printf("%d. %s \n" , i , array[i]);	   
    
    
    return 0;
}*/

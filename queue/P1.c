#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct my_msgbuf{
	long id;
	char message[5][10];
	
};
struct second{
	long id;
	int index;
};
int main (int argc , char *argv[]){
    //P1
    printf("P1 called\n");
    	char array[50][5] ; 
	
   	
     	for(int i=0 ; i<50 ; i++){
	     
	   for (int j = 0 ; j<5 ; j++){
		  array[i][j] = 'a' + (rand() %26 ) ;
	   }
	  array[i][4] = '\0';
	 
	    
	}


	//Sending message with queue
	struct my_msgbuf buf;
	struct second buf2;
	int  sendid , getid;
	key_t sendkey , getkey;
	if( (sendkey = ftok("P1.c" , 'B' )) == -1 || (getkey = ftok("P2.c" , 'C' ) ) == -1){
		perror("ftok");
		exit(1);
	}
	if ( (  sendid =  msgget (sendkey , 0644 ) ) == -1  || ( getid = msgget(getkey , 0644 )) == -1)
		{
			perror("msgget");
		exit(1);}
	
	for(int i=0 ; i<50 ; i++ ){

	buf.id = 1;
	for(int j=0 ; j<5 ; j++ ){
		if(i>=50){
			break;}
		strncpy(buf.message[j] , array[i] ,sizeof(array[0]));
		buf.message[j][5] = '0'+ (int)(i/10);
		buf.message[j][6] = '0' + (i%10);
		i++;
	}
	
	if(msgsnd(sendid , &buf , sizeof(buf.message) , 0) == -1)
        		perror("msgsnd");

	//printf("Message sent) \n"); 
	i--;
	while(1){
		if(msgrcv(getid , &buf2 , sizeof(buf2.index) , 0, 0 ) == -1)
			perror("msgsnd");
		else{

			if( buf2.index == i ){
				printf("\ncorrect id recieved by P2 \n\n");
			break;}
			else
			{	printf("Wrong message delivered by P2 expected %d got %d \n" ,i,buf2.index );
				exit(1);}
			}
		}
	}
		while(1){
		sleep(1);}
return 0;
}

	
/*

   for(int i=0 ; i<50 ; i++)
       printf("%d. %s \n" , i , array[i]);	   
    
    
    return 0;
}*/

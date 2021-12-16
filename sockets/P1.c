#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

#define SOCK_PATH "mysocket"
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
	struct sockaddr_un client;
	char str[10];
	int sock;
	if( (sock = socket(AF_UNIX , SOCK_STREAM , 0 )) == -1) {
		perror("socket");
		exit(1);}
	client.sun_family = AF_UNIX;
	strcpy(client.sun_path , SOCK_PATH) ;
	if( connect(sock, (struct sockaddr *)&client , strlen(client.sun_path) + sizeof(client.sun_family) ) ==-1){
		
		perror("connect");
		exit(1);}


	for(int i=0 ; i<50 ; i++ ){
		



		strncpy( str, array[i] ,sizeof(array[0]));
		str[5] = '0'+ (i/10);
		str[6] = '0' + (i%10);
		
		printf(" SENDING %s too  P2 %c%c \n" , str,str[5],str[6]);

	
		if(send ( sock , str , 10 , 0 ) == -1) {
			perror("send");
			exit(-1);
		}

		if( (i+1) % 5 == 0) {
			printf("waiting for confirmation \n" );
			//reciene from P2/server
			int got;
			if( (got = recv(sock , str , 2 , 0 )) < 0 ) {
				printf("recv");
				exit(1);}

			
			str[2] = '\0';

			 int d = 10*(str[0]-'0' ) + str[1] -'0';
			if(d!=i){
				printf("Wrong value recovered wanted %d got %d \n",i ,d );
				exit(0);}
			
			printf("\n value verified\n\n");
		}	

	}
	close(sock);
	

return 0;
}

	
/*

   for(int i=0 ; i<50 ; i++)
       printf("%d. %s \n" , i , array[i]);	   
    
    
    return 0;
}*/

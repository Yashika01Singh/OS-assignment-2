#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "mysocket"

int main (int argc , char *argv[]){
    //P2
    	 
	printf("P2 running \n");

	struct sockaddr_un name , remote;
	int connection_socket;
	char buffer[10];
	//uunlinking if socket already created
	unlink(SOCK_PATH);
	if(  (connection_socket = socket(AF_UNIX, SOCK_STREAM,0) ) == -1){
		perror("socket");
		exit(-1);}
	
	name.sun_family = AF_UNIX;
	strcpy(name.sun_path , SOCK_PATH);

	if( (bind(connection_socket , (struct sockaddr *)&name , sizeof(name.sun_family) + strlen(name.sun_path)) ) == -1){
		perror("bind");
		exit(1);}
	//bind is successfull
	int i = 0;
	if(listen(connection_socket , 5 ) == -1) {
		perror("listen");
		exit(1);
	}
	//now recieving remote connection
	int rem;
	char m[2];
	for( ;; ) {
		int lenrem = sizeof(remote);
		if( (rem = accept(connection_socket , (struct sockaddr *)&remote , &lenrem ) ) == -1){
			perror("accept");
			exit(1);}
		//socket connected
		while(1){
		memset(buffer , 0 , 10);
		int ret;
		if ( (  ret = recv ( rem , buffer , 10, 0) ) ==-1) {
			perror("recv");
			exit(1);}
		i++;
		
		m[0] = buffer[5];
		m[1]= buffer[6];
		if(ret==0){
			close(rem);
			return (0);}	
		printf("Recieved %s with id %c%c \n" , buffer, m[0] , m[1] );
		//recieved 5 string send back confirmation
		if(i%5==0){
		printf("sending signal back to client \n");
		if( send( rem , m , 2 , 0) <0 ) {
		       perror("send") ;
	       		}
		}	
		}		
}
return 0;

}

	


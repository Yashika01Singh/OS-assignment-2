#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/stat.h>
int main (int argc , char *argv[]){
    //P2
    	 
	printf("P2 running \n");

	//Recieving message with queue
	
	char str[5][10];
	mknod( "myfifo" , S_IFIFO | 0666 , 0);
	mknod( "feedback" , S_IFIFO | 0666,0);
	int num, fd, feedback;
	
	
	char m[2];	
	while(1){
	fd = open("myfifo" , O_RDONLY);	
		
		memset(str , 0 , sizeof(str) );
		if((num=read(fd , str , sizeof(str))) == -1) 
				perror("read");
		else{
			if(strcmp(str[0],"end") == 0){
				//all strings recieved
				return 0;}
			for(int j=0 ; j<5 ;j++){
			m[0] = str[j][5];
			m[1]= str[j][6];
			
			printf("Recieved %s with id %c%c \n" , str[j], m[0] , m[1] );
			}
		}
		
	
	feedback = open("feedback" , O_WRONLY);
	printf("sending confirmation\n");
	if(write(feedback, m , 2) == -1)
	
	perror("write");
	
	close(feedback);
	close(fd);
	}
	

	
	
	
return 0;

}

	


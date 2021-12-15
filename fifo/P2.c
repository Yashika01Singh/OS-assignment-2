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
	
	char str[10];
	mknod( "myfifo" , S_IFIFO | 0666 , 0);
	
	int num, fd;
	fd = open( "myfifo" , O_RDONLY) ;
	char m[2];	
	while(1){
	do{
		if((num=read(fd , str , 10)) == -1) 
				perror("read");
		else{
		m[0] = str[5];
		m[1]= str[6];
			
		printf("Recieved %s with id %c%c \n" , str, m[0] , m[1] );

		}
	

	}while(num>0);
	
	close(fd);
	fd=open("myfifo" , O_WRONLY);
	
	if(write(fd , m , 2) == -1)
		perror("write");
	
	close(fd);
	fd = open("myfifo" , O_RDONLY);
	}
	
return 0;

}

	
/*

   for(int i=0 ; i<50 ; i++)
       printf("%d. %s \n" , i , array[i]);	   
    
    
    return 0;
}*/

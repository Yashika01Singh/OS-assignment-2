#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

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
	mknod("myfifo" , S_IFIFO | 0666 ,0 );
	printf("sending a message \n" ) ;
	char str[10];
	int fd;
	fd = open ("myfifo" , O_WRONLY);
	for(int i=0 ; i<50 ; i++ ){
		



		strncpy( str, array[i] ,sizeof(array[0]));
		str[5] = '0'+ (i/10);
		str[6] = '0' + (i%10);
		
		printf(" SENDING %s too  P2 %c%c \n" , str,str[5],str[6]);

	
		if(write(fd,str,sizeof(str)) == -1)
			perror("write");

		if( (i+1) % 5 == 0) {
			sleep(1);
			close(fd);
			//open for reading
			fd = open("myfifo" , O_RDONLY);
			if(read(fd , str , 2 ) == -1)
		       		perror("read");
			str[2] = '\0';

			 int d = 10*(str[0]-'0' ) + str[1] -'0';
			if(d!=i){
				printf("Wrong value recovered wanted %d got %d \n",i ,d );
				exit(0);}
			close(fd);
			fd = open("myfifo" , O_WRONLY);
			printf("\n value verified\n\n");
		}	

	}
	

return 0;
}

	
/*

   for(int i=0 ; i<50 ; i++)
       printf("%d. %s \n" , i , array[i]);	   
    
    
    return 0;
}*/

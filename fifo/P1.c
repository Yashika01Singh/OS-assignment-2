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
	mknod("feedback" , S_IFIFO | 0666 , 0) ;
	printf("sending a message \n" ) ;
	char str[5][10];
	char index[2];
	int fd, feedback;

	for(int i=0 ; i<50 ; i++ ){
		
		for(int j=0 ; j<5 ;j++){


		strncpy( str[j], array[i] ,sizeof(array[0]));
		str[j][5] = '0'+ (i/10);
		str[j][6] = '0' + (i%10);
		printf("sending %s %d \n" , array[i] , i);
		i++;
		}
		i--;
		
		fd = open("myfifo" , O_WRONLY);
	
			if(write(fd,str,sizeof(str)) == -1)
			perror("write");

		close(fd);
			printf("waiting confirmation \n");	
			
			//open for reading
			feedback = open("feedback" , O_RDONLY);
			if(read(feedback , index , 2 ) == -1)
		       		perror("read");
		

			 int d = 10*(index[0]-'0' ) + index[1] -'0';
			if(d!=i){
				printf("Wrong value recovered wanted %d got %d \n",i ,d );
				exit(0);}
			
			printf("\n value verified\n\n");
			close(feedback);
			
	
		
		}
	strncpy(str[0] , "end" , 4) ;
	fd=open("myfifo" , O_WRONLY);
	if ( write(fd , str , sizeof(str) ) == -1)
		perror("write");
	close(fd);



return 0;
}

	
/*

   for(int i=0 ; i<50 ; i++)
       printf("%d. %s \n" , i , array[i]);	   
    
    
    return 0;
}*/

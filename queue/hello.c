#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>



int main()
{/*
pid_t f1;*/

	
   int msqid1, msqid2 ;
   key_t key1 , key2;

   if(  (key1 = ftok("P1.c" , 'B') )== -1 ||  (key2 = ftok ("P2.c" , 'C' ) ) ==-1) {
	   perror("ftok");
	   exit(1);
   }
  
   if( ( msqid1 = msgget(key1 , 0664 | IPC_CREAT)) == -1 ||  ( msqid2 = msgget(key2 , 0664 | IPC_CREAT)) == -1) {
	   perror("msgget");
	   exit(1);
   
	}	
   pid_t pid ;
   printf("next\n");
   pid = fork();
   
   if(pid<0)
        { printf("Fork Failed\n");
         
         }

   if(pid==0){
         

            
            //P1
            
   
            execl("P1","P1" , NULL , NULL);
           exit(1);
      }
      //parent process
   else{     
   	

            execl("P2","P2" ,NULL , NULL);
     
}         
   

}

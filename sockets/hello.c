#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>



int main()
{ 
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

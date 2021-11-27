#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


void s1_sigterm_handler (int signum, siginfo_t *info, void *ptr){
  
   printf("Value passed %d " , info->si_value.sival_int);
  printf("Terminator called:\n");
}

int main()
{

  
   pid_t pid , ultim;
   
   pid = fork();
   
   if(pid<0)
        { printf("Fork Failed\n");
         
         }

   if(pid==0){
         
      
         printf("child S1 %d  \n", getpid() );
         struct sigaction act;
         act.sa_sigaction = s1_sigterm_handler;
         act.sa_flags = SA_SIGINFO;
         sigaction(SIGTERM, &act, 0);
         int i=0;
	
    	
	 while(1){
            
            int a =sleep(1);
            printf("child is sleeping\n");

	    
            i++;           

            
         }
         
        
         
         exit(0);
   }   
   
   
   ultim = pid;
   
    
    
   pid = fork();

          
      if(pid<0)
        { 
           printf("Fork Failed\n");       
         }

      if(pid==0){
            
            //SR
            
          
            char arg1[20];
            snprintf(arg1, sizeof(arg1), "%d", ultim);;
   
            execl("E1","E1" , arg1 , NULL);
            
      }
      //parent process
      pid = fork();
      if(pid<0)
        { printf("Fork Failed\n");
         
         }
      if(pid==0){
            
            char arg1[20];
            snprintf(arg1, sizeof(arg1), "%d",ultim);;
   
            execl("E2","E2" , arg1, NULL);
           
      }
      //parent process
      
	wait(NULL);     
 	wait(NULL);
   	wait(NULL);	
      printf("parent process finished");
      
   

}

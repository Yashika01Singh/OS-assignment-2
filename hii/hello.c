#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>



void s1_sigterm_handler (int signum, siginfo_t *info, void *ptr){
   
    union sigval value = info->si_value;
     printf("\n... Process terminated ... %d" ,value.sival_int);
  printf("Got a signal from %d. The message was: %s\n", info->si_pid, (char*) value.sival_ptr);
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
            printf(" %d stopp " , i);
            int a =sleep(1);
            printf("%d \n" ,a);
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
      
     
      
      printf("parent process finished");
      
   

}

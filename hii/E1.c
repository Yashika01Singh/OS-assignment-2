#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

pid_t ID;
void s1_siglarm_handler (){
    printf("\nhii im a alarm for E1%d \n" , ID);
    unsigned long long rand;
    asm volatile ("rdrand %0 \n\t":"=a"(rand)::);
    union sigval value;
    value.sival_int = (int)rand;
    sigqueue(ID, SIGTERM, value);
}

int main (int argc , char *argv[]){
    ID = strtol(argv[1] , NULL , 10 );
   // printf("E1 called with ID %d and its ID is %d\n" , ID , getpid());
    
    signal(SIGALRM , s1_siglarm_handler);
    
    kill(getpid(), 14);
    
    
    
    return 0;
}

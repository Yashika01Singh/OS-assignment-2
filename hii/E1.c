#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

pid_t ID;
void s1_siglarm_handler (){
    printf("\nhii im a alarm %d \n" , ID);
    int rand = 5050505;
    union sigval value;
    value.sival_int = rand;
    sigqueue(ID, SIGTERM, value);
}

int main (int argc , char *argv[]){
    ID = strtol(argv[1] , NULL , 10 );
    printf("E1 called with ID %d and its ID is %d\n" , ID , getpid());
    
    signal(SIGALRM , s1_siglarm_handler);
    
    kill(getpid(), 14);
    
    
    
    return 0;
}
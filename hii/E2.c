#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
pid_t ID;
void s2_siglarm_handler (){
    printf("\ntimer hit %d \n" , ID);
        
    union sigval value;
    value.sival_ptr = "this is random string time";
    sigqueue(ID, SIGTERM, value);
}

int main (int argc , char *argv[]){
    ID = strtol(argv[1] , NULL , 10 );
    printf("E2 called with ID %d and its ID is %d\n" , ID , getpid());
    struct sigaction act;
    struct itimerval timer;
    
    act.sa_sigaction =s2_siglarm_handler;
 	act.sa_flags = SA_SIGINFO;
	sigaction(SIGALRM , &act , NULL);

    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 5;
    timer.it_interval.tv_usec=0;
    int ret = setitimer(ITIMER_REAL , &timer , NULL);
    
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

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
    
    signal(SIGALRM , s2_siglarm_handler);
    struct itimerval delay;
 int ret;

 delay.it_value.tv_sec = 5;
 delay.it_value.tv_usec = 0;
 delay.it_interval.tv_sec = 1;
 delay.it_interval.tv_usec = 0;
 ret = setitimer (ITIMER_REAL, &delay, NULL);
 if (ret) {
 perror ("setitimer");
 return 0;
 }

    
    
    return 0;
}
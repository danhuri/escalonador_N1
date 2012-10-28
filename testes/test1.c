#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define debug(msg) printf(msg);printf("\n")


void *func1(void *arg)
{
    printf("func1: started\n");
    printf("func1: %d\n",*(int*)arg);
    uthread_yield();
    printf("func1: %d - returning\n",*(int*)arg);
    return NULL;
}


int main(void)
{      
    int arg=199, arg2=200, tid1=-1, tid2=-1;
    libuthread_init();    
    
    tid1 = uthread_create(func1,&arg);
    tid2 = uthread_create(func1,&arg2);
    
 
    if (tid1==-1)
	handle_error("Erro ao criar thread");
    //uthread_join(tid1);
    if (uthread_yield()!=0)
	handle_error("Erro ao realizar yield");
        
    debug("main process");
    
    if (uthread_yield()!=0)
	handle_error("Erro ao realizar yield");
    
    printf("main: exiting\n");
    return 0;    
}


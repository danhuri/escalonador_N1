#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define debug(msg) printf(msg);printf("\n")


void *func1(void *arg)
{
    int i;
    printf("func1: started\n");
    printf("func1: %d\n",*(int*)arg);
    for (i=0; i<10; i++) {
	printf ("func1 i = %d\n",i);
        uthread_yield();
    }
    printf("func1: %d - returning\n",*(int*)arg);
    return NULL;
}


int main(void)
{      
    int arg=199, tid1, i;
    libuthread_init();    
    tid1 = uthread_create(func1,&arg);    
    if (tid1==-1)
	handle_error("Erro ao criar thread");
    //uthread_join(tid1);
    for (i=0; i<10; i++) {
	printf("main i: %d ", i);
        if (uthread_yield()!=0)
	    handle_error("Erro ao realizar yield");
    }        
    printf("main: exiting\n");
    return 0;    
}


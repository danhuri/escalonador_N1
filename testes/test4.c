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

void *func2(void *arg)
{
    int i;
    printf("func2: started\n");
    printf("func2: %d\n",*(int*)arg);
    for (i=0; i<10; i++) {
	printf ("func2 i = %d\n",i);
        uthread_yield();
    }
    printf("func2: %d - returning\n",*(int*)arg);
    return NULL;
}



int main(void)
{      
    int arg=199, arg2=200, tid1, tid2;
    libuthread_init();    
    
    tid1 = uthread_create(func1,&arg);
    tid2 = uthread_create(func2,&arg2);
 
    if (tid1==-1 || tid2==-1)
	handle_error("Erro ao criar thread");
    
    uthread_join(tid2);
    uthread_join(tid1);
        
    printf("main: exiting\n");
    return 0;
    
}


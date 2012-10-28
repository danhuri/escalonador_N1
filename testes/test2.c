#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define debug(msg) printf(msg);printf("\n")

void *func2(void *arg);

void *func1(void *arg)
{
    int *ti=(int*)arg;
    printf("func1: started\n");
    printf("func1: %d\n",*(int*)arg);
    
    //Testando comunicacao entre threads, atraves da variavel i
    for ( ; *ti<10; (*ti)++) {
	printf ("func1 i = %d\n",*ti);
        uthread_yield();
    }

    printf("func1: %d - returning\n",*(int*)arg);
    return NULL;
}

void *func2(void *arg)
{
    int *ti=(int*)arg;
    printf("func2: started\n");
    printf("func2: %d\n",*(int*)arg);
    for ( ; *ti<10; (*ti)++) {
	printf ("func2 i = %d \n",*ti);
        uthread_yield();
    }
    printf("func2: %d - returning\n",*(int*)arg);
    return NULL;
}



int main(void)
{      
    int arg=0, tid1, tid2;
    libuthread_init();    
    
    tid1 = uthread_create(func1,&arg);
    tid2 = uthread_create(func2,&arg);

    if (tid1==-1 )
	handle_error("Erro ao criar thread");
    
    uthread_join(tid1);
    uthread_join(tid2);
        
    printf("main: exiting\n");
    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define debug(msg) printf(msg);printf("\n")


void *func1(void *arg)
{
    int *i = (int*)arg;
    printf("%d, ", ++(*i));
    uthread_yield();
    printf("%d, ", --(*i));
    return NULL;
}

int cria_thread(int i)
{
   return uthread_create(func1,&i);
}

int main(void)
{      
    int tid[100], i, j;
    libuthread_init();       
    for (i=0; i<100; i++) { 
        tid[i] = cria_thread(i);
        if (tid[i]==-1)
            handle_error("Erro ao criar thread");      
    }   
    for (j=0; j<100; j++) 
        uthread_join(tid[j]);    
    printf("main: exiting\n");
    return 0;    
}


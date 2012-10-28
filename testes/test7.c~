#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define debug(msg) printf(msg);printf("\n")

int tidglobal[128];
int erro[128] = {0};

void *func1(void *ptid)
{
    int tid = *(int*)ptid;
    printf("thread %d esperando thread: %d \n", tidglobal[tid],tid);
    if (uthread_join(tid)==-1) {
        printf("Deadlock\n");
        erro[tidglobal[tid]]=1;
        return NULL;
    }

    if (erro[tid]) {
        erro[tidglobal[tid]]=1;
        printf("Erro no thread: %d , thread %d abortado! \n", tid, tidglobal[tid]);
    }
    else 
        printf("Fim Normal do thread: %d \n", tidglobal[tid]);

    return NULL;
}

int main(void)
{      
    int tid[3];
    int val[3];
    libuthread_init();    
   

    tid[0] = uthread_create(func1,&val[0]);
    tid[1] = uthread_create(func1,&val[1]);
    tid[2] = uthread_create(func1,&val[2]);

    //val contem o tid do thread com o qual deve ser sincronizado
    val[0]=tid[1];
    val[1]=tid[2];
    val[2]=tid[0];

    //tidglobal contem o inverso do 'val', o tid do proc. que fez a sincronização
    tidglobal[tid[0]]=tid[2];
    tidglobal[tid[1]]=tid[0];
    tidglobal[tid[2]]=tid[1];


    if (uthread_join(tid[0])==-1)
        handle_error("Erro de sincronização");
    
    
    printf("main: exiting\n");
    return 0;
    
}


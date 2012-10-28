#include "../include/uthread_queue.h"
#include <stdio.h>
#include <stdlib.h>

//Inicializa com NULL os ponteiros da fila
void init_queue(uthread_queue *queue)
{
    queue->first=NULL;
    queue->last=NULL;
}

//Adiciona um processo a uma fila
int enqueue(uthread_queue *queue, uthread_t *thr)
{
    queue_elem *new_elem;
    if (queue==NULL)
       return -1; 
    new_elem = malloc(sizeof(queue_elem));
    if (new_elem==NULL)
        return -1;
    new_elem->thread=thr;
    new_elem->next=NULL;
    if (queue->first==NULL) {
        queue->first=new_elem;
        queue->last=new_elem;
    }
    else {
        queue->last->next=new_elem;
        queue->last=new_elem;    
    }
    return 0;
}

//Retira uma thread da fila
uthread_t * dequeue(uthread_queue *queue)
{
    uthread_t * removing_thr;
    queue_elem * elemaux;
    
    /*
    printf("queue before ");
    for (elemaux=queue->first; elemaux!=NULL; elemaux=elemaux->next)
        printf("tid: %d  ", elemaux->thr->tid);
    */
    
    if (queue==NULL)
        return NULL;
    if (queue->first==NULL)
        return NULL;
    else {
        removing_thr=queue->first->thread;
        elemaux=queue->first->next;
        free(queue->first);
        queue->first=elemaux;
        if (elemaux==NULL)
	    queue->last=NULL;
        /*for (elemaux=queue->first; elemaux!=NULL; elemaux=elemaux->next)
            printf("pid: %d  ", elemaux->proc->pid);
        */
        return removing_thr;
    }
}


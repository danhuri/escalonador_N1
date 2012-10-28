#include "../include/uthread_queue.h"
#include "../include/uthread.h"
#include <stdio.h>
#include <stdlib.h>

//Usado para busca de TIDs
#define MAXTID 128
#define STACK_SIZE 16384

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0);
#define debug(msg) printf(msg);printf("\n");


int find_tid();
int scheduler();


uthread_queue ready_queue;
uthread_t *running_thr = NULL;
ucontext_t scheduler_ctx;

uthread_t *thr_arr[MAXTID] = {0};

//int deadlock = 0;
//int uthread_deadlock()
//{
//    return deadlock;
//}

//Encontra um TID disponivel percorrendo o array thr_arr
int find_tid(void)
{
    int i;
    for (i=0; i<MAXTID && thr_arr[i]!=NULL; i++) { }
    
    return i;
}

int scheduler(void)
{
    uthread_t *t;
    // Se estado Running, o processo terminou normalmente
    // entao transfere bloqueados para Ready, desaloca e escalona
    //deadlock=0;
    if (running_thr->state==running) {
        //transferindo bloqueados
        for (t=dequeue(&running_thr->waiting_queue); t!=NULL; t=dequeue(&running_thr->waiting_queue)) {
            if (enqueue(&ready_queue,t)!=0)
                handle_error("Erro de alocacao ao enfileirar threads bloqueadas");
        }
	//libera TID
        thr_arr[running_thr->tid]=NULL;
	free(running_thr->context.uc_stack.ss_sp);
        free(running_thr);
        running_thr = dequeue(&ready_queue);
        //Dispatch: seta estado e troca contexto
	running_thr->state=running;
        setcontext(&running_thr->context);
    }
    else {
        t=running_thr;
        running_thr=dequeue(&ready_queue);

	/*Se Nao Ha threads na fila: 
	    Se caller=yield recoloca o mesmo processo a executar
	    Senao caller=Join e houve Join de processo inexistente, falha
	    */
        if (running_thr==NULL) {                
            running_thr=t;
            if (running_thr->state == blocked) {
                running_thr->state = running;
                return -1;  //deadlock -> tentou sincronizar mas nao há mais processos no estado Ready.
            }
        }
        running_thr->state=running;
        swapcontext(&t->context, &running_thr->context);            
    }
    return 0;
}

int uthread_join(int tid)
{
    //deadlock=0;
    if (running_thr == NULL)
	return -1;
    if (thr_arr[tid]!=NULL) {
        running_thr->state=blocked;
	//Coloca o processo na fila de Espera do processo apontado por pid
        if (enqueue(&thr_arr[tid]->waiting_queue,running_thr) == -1) {
            running_thr->state=running;
            return -1;
        }
        if (scheduler() == -1) {
            //deadlock = 1;
            return -1; //Deadlock
        }
    }
    return 0;
}

int uthread_yield(void)
{
    if (running_thr == NULL)
	return -1;
    //Coloca o processo no fim da fila
    if (enqueue(&ready_queue, running_thr)!=0)
        return -1;
    //Setar o estado configura o comportamento do scheduler
    running_thr->state = ready;
    scheduler();
    return 0;
}

char scheduler_stack[4096];

int libuthread_init(void)
{
    init_queue(&ready_queue);
    //Aloca processo para o Main com tid 0
    running_thr = malloc(sizeof(uthread_t));
    if (running_thr==NULL)
	return -1;
    running_thr->tid=0;
    running_thr->state=running;
    init_queue(&running_thr->waiting_queue);
    thr_arr[0]=running_thr;

    //Cria um Contexto para o scheduler, utilizado no termino dos processos criados
    if (getcontext(&scheduler_ctx) == -1) {
        free(running_thr);
        return -1; 
    }
    scheduler_ctx.uc_stack.ss_sp=scheduler_stack;
    scheduler_ctx.uc_stack.ss_size=sizeof(scheduler_stack);
    scheduler_ctx.uc_link=NULL;
    makecontext(&scheduler_ctx, (void(*)())scheduler, 0);
    return 0;
}

int uthread_create(void * (*start_routine)(void*), void *arg)
{
    uthread_t *newthr;
    
    if (running_thr == NULL) 
	return -1;
    //newthr contem a nova thread alocada
    newthr = malloc(sizeof(uthread_t));
    if (newthr == NULL)
        return -1;
    //inicializa a fila de espera
    init_queue(&newthr->waiting_queue);
    newthr->state=ready;
    if (getcontext(&newthr->context)==-1) {
	free(newthr);
        return -1;
    }
    //aloca memoria para a pilha do processo
    newthr->context.uc_stack.ss_sp=malloc(STACK_SIZE);
    if (newthr->context.uc_stack.ss_sp==NULL) {
	free(newthr);
	return -1;
    }
    newthr->context.uc_stack.ss_size=STACK_SIZE;
    //indica com uc_link que após o término do processo o controle passa ao scheduler
    newthr->context.uc_link=&scheduler_ctx;
    makecontext(&newthr->context, (void(*)())start_routine, 1, arg);
    if (enqueue(&ready_queue, newthr)!=0) {
	free(newthr->context.uc_stack.ss_sp);
	free(newthr);
	return -1;
    }
    //acha um TID e coloca a nova thread no vetor indexado por TID
    newthr->tid=find_tid();
    thr_arr[newthr->tid]=newthr;

    return newthr->tid;
}


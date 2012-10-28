#ifndef __uthread_queue
#define __uthread_queue

#include <ucontext.h>

enum state_e {
    ready=1,
    running,
    blocked
};

typedef struct _queue_elem {
    struct _uthread_t *thread;
    struct _queue_elem *next;
} queue_elem;

typedef struct {
    queue_elem *first;
    queue_elem *last;    
} uthread_queue;


typedef struct _uthread_t {
    int tid;
    ucontext_t context;
    enum state_e state;
    uthread_queue waiting_queue;
} uthread_t;

void init_queue(uthread_queue *queue);
int enqueue(uthread_queue *queue, uthread_t *proc);
uthread_t * dequeue(uthread_queue *queue);

#endif


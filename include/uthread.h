
int uthread_join(int pid); // thread
int uthread_yield();
int libuthread_init();
int uthread_create(void * (*start_routine)(void*), void *arg);
//int uthread_deadlock();

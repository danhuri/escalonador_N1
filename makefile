cc=gcc

all: uthread

uthread: ./lib/libuthread.a

./lib/libuthread.a: ./bin/uthread_queue.o ./src/uthread.c
	$(cc) -o ./bin/uthread.o -c ./src/uthread.c -Wall
	ar crs ./lib/libuthread.a ./bin/uthread.o ./bin/uthread_queue.o

./bin/uthread_queue.o: ./src/uthread_queue.c
	$(cc) -o ./bin/uthread_queue.o -c ./src/uthread_queue.c -Wall

clean:  
	rm ./lib/*.a
	rm ./bin/*.o

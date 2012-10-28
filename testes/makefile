cc=gcc

#user% gcc -o exemplo exemplo.c -L../lib -luthread -Wall

all: test1 test2 test3 test4 test5 test6 test7

test1: test1.c ../lib/libuthread.a
	$(cc) -o ../bin/test1 test1.c -L../lib -luthread -Wall

test2: test2.c ../lib/libuthread.a
	$(cc) -o ../bin/test2 test2.c -L../lib -luthread -Wall

test3: test3.c ../lib/libuthread.a
	$(cc) -o ../bin/test3 test3.c -L../lib -luthread -Wall

test4: test4.c ../lib/libuthread.a
	$(cc) -o ../bin/test4 test4.c -L../lib -luthread -Wall

test5: test5.c ../lib/libuthread.a
	$(cc) -o ../bin/test5 test5.c -L../lib -luthread -Wall

test6: test6.c ../lib/libuthread.a
	$(cc) -o ../bin/test6 test6.c -L../lib -luthread -Wall

test7: test7.c ../lib/libuthread.a
	$(cc) -o ../bin/test7 test7.c -L../lib -luthread -Wall

clean:
	rm ../bin/*.o
	rm ../bin/test1
	rm ../bin/test2
	rm ../bin/test3
	rm ../bin/test4
	rm ../bin/test5
	rm ../bin/test6
	rm ../bin/test7


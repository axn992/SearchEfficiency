all: main.o main-test.o libutil.o libset.o
	gcc -W -Wall -D_XOPEN_SOURCE=500 -o set_search main.o libutil.o libset.o -lm
	gcc -W -Wall -D_XOPEN_SOURCE=500 -o maintest main-test.o libutil.o libset.o -lm

main.o: main.c 
	gcc -W -Wall -D_XOPEN_SOURCE=500 -c main.c

main-test.o: main-test.c 
	gcc -W -Wall -D_XOPEN_SOURCE=500 -c main-test.c	
	
libutil.o: libutil.c libutil.h
	gcc -W -Wall -D_XOPEN_SOURCE=500 -c libutil.c

libset.o: libset.c libset.h
	gcc -W -Wall -D_XOPEN_SOURCE=500 -c libset.c

clean:
	rm -rf *.o core set_search maintest *.errs

test: main-test.c
	./maintest

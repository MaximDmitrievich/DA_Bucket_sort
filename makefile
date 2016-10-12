FLAGS=-g -pedantic -Wall -std=c99 -Werror -Wno-sign-compare
CC=gcc

all: stringsio data main.c
	$(CC) -c $(FLAGS) main.c
	$(CC) $(FLAGS) -o Bucket_sort stringsio.o data.o main.o

data: data.c
	$(CC) -c $(FLAGS) data.c

stringsio: stringsio.c
	$(CC) -c $(FLAGS) stringsio.c

tester: tester.c
	$(CC) -c $(FLAGS) tester.c
	$(CC) $(FLAGS) -o Tester stringsio.o tester.o

clean:
	rm -f *.o
	rm -f *.txt
	rm -f *.stackdump

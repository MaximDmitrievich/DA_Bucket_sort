FLAGS=-pedantic -Wall -std=c99 -Werror -Wno-sign-compare
CC=gcc

all: start

start:  data.o strings.o main.o
	$(CC) $(FLAGS) -o Bucket_sort data.o strings.o main.o

main.o: main.c
	$(CC) -c $(FLAGS) main.c

data.o: data.c
	$(CC) -c $(FLAGS) data.c

strings.o: strings.c
	$(CC) -c $(FLAGS) strings.c

clear:
	-rm -f *.o Bucket_sort

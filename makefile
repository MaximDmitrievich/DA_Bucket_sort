FLAGS=-g -pedantic -Wall -std=c99 -Werror -Wno-sign-compare
CC=gcc

all: strings data main.c
	$(CC) -c $(FLAGS) main.c
	$(CC) $(FLAGS) -o Bucket_sort strings.o data.o main.o

data: data.c
	$(CC) -c $(FLAGS) data.c

strings: strings.c
	$(CC) -c $(FLAGS) strings.c

clean:
	rm -f *.o
FLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -w -pipe -O3 -fno-exceptions
CC = gcc
PROGRAM = Bucket_sort.exe

all: main.c string data strings.h data.h
	$(CC) $(FLAGS) main.c -L. -Wl,-rpath,. -o $(PROGRAM)

string: strings.c strings.h
	$(CC) $(FLAGS) -c strings.c

data: data.c data.h
	$(CC) $(FLAGS) -c data.c

clean:
	rm -f *.o

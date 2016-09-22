FLAGS=-pedantic -Wall -std=c99 -Werror -Wno-sign-compare -lm
COMPILLER=gcc

all: start

start:  data.o strings.o main.o
	$(COMPILLER) $(FLAGS) -o Bucket_sort data.o strings.o main.o

main.o: main.c
	$(COMPILLER) -c $(FLAGS) main.c

data.o: data.c
	$(COMPILLER) -c $(FLAGS) data.c

strings.o: strings.c
	$(COMPILLER) -c $(FLAGS) strings.c

clear:
	-rm -f *.o *.gch Bucket_sort

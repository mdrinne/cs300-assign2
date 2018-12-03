

LOPTS = -Wall -Wextra -std=c99 -g

all : p420 p421

p420 :
	gcc $(LOPTS) -c p420.c
	gcc $(LOPTS) p420.o -o p420 -lpthread

p421 :
	gcc $(LOPTS) -c p421.c
	gcc $(LOPTS) p421.o -o p421 -lpthread

clean :
	rm -f p420 p421 p420.o p421.o

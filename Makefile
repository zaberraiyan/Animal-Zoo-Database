a.out: p9.o operations.o
	gcc p9.o operations.o

p9.o: p9.c operations.h
	gcc -std=c99 -c p9.c

operations.o: operations.c operations.h
	gcc -std=c99 -c operations.c

clean:
	rm -f test p9.o operations.o
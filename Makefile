all: dir.out

dir.out: dir.o
	gcc dir.o -o dir.out

run: all
	./dir.out

dir.o: dir.c
	gcc -c dir.c

clean:
	rm *.o *.out

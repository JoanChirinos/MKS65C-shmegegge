compile: shared_mem.o
	gcc shared_mem.o

run:
	./a.out

clean:
	-rm -rf ./a.out *.o

shared_mem.o:
	gcc -c shared_mem.c

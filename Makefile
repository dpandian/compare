all:
	gcc -g compare.c -o compare

clean:
	rm compare compare.o

test:
	./compare 5   1 2 5 7 12 14


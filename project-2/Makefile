all: cat1

run: cat1
	./cat1

cat1: cat1.o
	gcc cat1.o -o cat1

cat1.o: cat1.c
	gcc -c cat1.c

clean:
	rm -f cat1


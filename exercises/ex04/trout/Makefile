all: trout.o util.o main.o trout

trout.o: trout.h trout.c util.h
	gcc -g -c trout.c

util.o: util.h util.c
	gcc -g -c util.c

main.o: main.c util.h trout.h
	gcc -g -c main.c

trout: trout.o util.o main.o
	gcc -g -o trout main.o trout.o util.o

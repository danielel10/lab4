all: exe

exe: util.o main.o start.o
	ld -m elf_i386 start.o main.o util.o -o exe

util.o: util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

main.o: main.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector main.c -o main.o

start.o: lab4_start.s
	nasm -f elf32 lab4_start.s -o start.o


.PHONY: clean
clean:
	rm -f *.o lab3_mergesort

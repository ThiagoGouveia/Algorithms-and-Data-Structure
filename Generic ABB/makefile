all:	exec

exec:	main.o ABBGen.o
	gcc -o exec main.o ABBGen.o

main.o:	main.c ABBGen.h
	gcc -c main.c	-w

ABBGen.o:	ABBGen.c ABBGen.h
		gcc -c ABBGen.c	-w

clean:
	rn main.o ABBGen.o exec

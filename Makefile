all:
	gcc -c ./lista.c -o lista.o
	gcc -c ./horario.c -o horario.o
	gcc -c ./main.c -o main.o
	gcc main.o horario.o lista.o -o main
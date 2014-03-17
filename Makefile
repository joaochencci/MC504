C = gcc
CFLAGS = -g -pthread

PROGRAMS = dica verificacao sudoku

all: $(PROGRAMS)

dica: dica.c
	gcc -o dica dica.c

verificacao: verificacao.c
	gcc -o verificacao verificacao.c

sudoku: sudoku.c
	gcc -o sudoku sudoku.c


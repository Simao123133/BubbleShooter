CC=gcc
CFLAGS=-g -I/usr/include/SDL2 -D_REENTRANT -std=c99 -O3
LDLIBS=-L/usr/lib/i386-linux-gnu -lm -lSDL2 -lSDL2_image -lSDL2_gfx

all: trabalhofinal

trabalhofinal: trabalhofinal.o grafica.o ficheiro.o ledados.o funcoes.o
	$(CC) $(CFLAGS) trabalhofinal.o grafica.o ficheiro.o ledados.o funcoes.o $(LDLIBS) -o trabalhofinal

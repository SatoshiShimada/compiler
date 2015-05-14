
CC=gcc
CFLAGS=-Wall -O2

src=main.c compile.c
outfile=compiler

default: $(src)
	$(CC) $(CFLAGS) $(src) -o $(outfile)
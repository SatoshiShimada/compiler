
CC=gcc
CFLAGS=-Wall -O2

src=main.c compile.c
outfile=compiler

default:
	make compiler
	make preprocessor

compiler: $(src)
	$(CC) $(CFLAGS) $(src) -o $(outfile)

preprocessor: preprocessor.c
	$(CC) $(CFLAGS) preprocessor.c -o preprocessor

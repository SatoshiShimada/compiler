
#include <stdio.h>

#include "compile.h"

int next_char(void);
Token next_token(void);

/* global variable */
FILE *fin;
char f_fp; /* flag of file pointer */

int compile(FILE *fp)
{
	fin = fp;
	f_fp = 1;
	
	f_fp = 0;
	return 0;
}

char next_char(void)
{
	char c;
	
	if(f_fp != 0) return (char)-1;
	
	c = fgetc(fin);
	
	return c;
}

Token next_token(void)
{
	Token token;
	
	return token;
}
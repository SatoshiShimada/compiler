
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "compile.h"

char next_char(void);
Token next_token(void);
int isoperator(int c);

/* global variable */
FILE *fin;
char f_fp; /* flag of file pointer */

int compile(FILE *fp)
{
	Token token;
	
	fin = fp;
	f_fp = 1;
	
	for(;;) {
		token = next_token();
		if(token.type == END_OF_FILE) break;
		
		printf("%d: %d\n", (int)token.type, token.value);
	}
	
	f_fp = 0;
	return 0;
}

char next_char(void)
{
	char c;
	
	if(f_fp == 0) return (char)-1;
	
	c = fgetc(fin);
	
	return c;
}

Token next_token(void)
{
	Token token;
	char c;
	char buf[100];
	int i;
	
	i = 0;
	
	c = next_char();
	if(c == EOF) {
		token.value = 0;
		token.type = END_OF_FILE;
		return token;
	} else if(isdigit(c)) {
		buf[i++] = c;
		for( ;; ) {
			c = next_char();
			if(!isdigit(c)) break;
			buf[i++] = c;
		}
		buf[i] = '¥0';
		token.value = atoi(buf);
		token.type = NUMBER;
	} else if(isoperator(c)) {
		token.value = c;
		token.type = OPERATOR;
		return token;
	} else {
			
	}
	
	return token;
}

int isoperator(int c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
	   c == '!' || c == '|' || c == '&' || c == '^')
	{
		return 1;
	} else {
		return 0;
	}
}
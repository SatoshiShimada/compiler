
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "compile.h"

char next_char(void);
Token next_token(void);
int init_token_type(void);

/* global variable */
FILE *fin;
char f_fp; /* flag of file pointer */
char token_type[256];
char f_init_type;

int compile(FILE *fp)
{
	Token token;
	
	fin = fp;
	f_fp = 1;
	
	token = next_token();
	if(token.type == END_OF_FILE) ;//break;
	
	printf("%d: %d\n", (int)token.type, token.value);
	
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
	
	if(f_init_type == 0) init_token_type();
	
	c = next_char();

	switch(token_type[c]) {
	case EOF:
		token.value = 0;
		token.type = END_OF_FILE;
		return token;
		break;
	case NUMBER:
		buf[i++] = c;
		for( ;; ) {
			c = next_char();
			if(token_type[c] != NUMBER) {
				ungetc(c, fin);
				break;
			}
			buf[i++] = c;
		}
		buf[i] = '\0';
		token.value = atoi(buf);
		token.type = NUMBER;
		break;
	case OPERATOR:
		token.value = c;
		token.type = OPERATOR;
		return token;
		break;
	default:
		break;
	}
	
	return token;
}

int init_token_type(void)
{
	int i;
	
	if(f_init_type == 1) return 0;
	
	for(i = 0; i < sizeof(token_type); i++) {
		token_type[i] = UNSET;
	}
	
	for(i = '0'; i < '9'; i++) {
		token_type[i] = NUMBER;
	}
	
	for(i = 'a'; i < 'z'; i++) {
		token_type[i] = CHAR;
	}
	
	for(i = 'A'; i < 'Z'; i++) {
		token_type[i] = CHAR;
	}
	
	token_type['_'] = CHAR;
	
	token_type[' '] = SPACE;
	token_type['\n'] = SPACE;
	token_type['\t'] = SPACE;
	
	token_type['!'] = OPERATOR;
	token_type['\"'] = OPERATOR;
	token_type['#'] = OPERATOR;
	token_type['%'] = OPERATOR;
	token_type['&'] = OPERATOR;
	token_type['\''] = OPERATOR;
	token_type['('] = OPERATOR;
	token_type[')'] = OPERATOR;
	token_type['*'] = OPERATOR;
	token_type['+'] = OPERATOR;
	token_type[','] = OPERATOR;
	token_type['-'] = OPERATOR;
	token_type['.'] = OPERATOR;
	token_type['/'] = OPERATOR;
	token_type['@'] = OPERATOR;
	token_type['['] = OPERATOR;
	token_type[']'] = OPERATOR;
	token_type['{'] = OPERATOR;
	token_type['}'] = OPERATOR;
	token_type['\\'] = OPERATOR;
	token_type['^'] = OPERATOR;
	token_type['`'] = OPERATOR;
	token_type['|'] = OPERATOR;
	token_type['~'] = OPERATOR;
	token_type['<'] = OPERATOR;
	token_type['>'] = OPERATOR;
	token_type[':'] = OPERATOR;
	token_type[';'] = OPERATOR;
	token_type['='] = OPERATOR;
	token_type['?'] = OPERATOR;
	
	f_init_type = 1;
	
	return 0;
}
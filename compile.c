
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int i;
	
	fin = fp;
	f_fp = 1;
	
	for(i = 0; i < 10000; i++) {
		token = next_token();
		if(token.type == END_OF_FILE) {
			break;
		}
		
		switch(token.type) {
		case NUMBER:
			printf("%d ", token.value);
			break;
		case CHAR:
			printf("%s ", token.string);
			break;
		case OPERATOR:
			printf("%c ", token.value);
			break;
		default:
			printf("* ");
			break;
		}
	}
	
	f_fp = 0;
	return 0;
}

char next_char(void)
{
	char c;
	
	if(f_fp == 0) return (char)-1;
	
	c = fgetc(fin);
	if(c == EOF) c = 0;
	
	return c;
}

Token next_token(void)
{
	Token token;
	char c;
	char buf[100];
	int i;
	int value;
	
	if(f_init_type == 0) init_token_type();

	token.value = 0;
	token.string[0] = '\0';
	token.type = UNSET;

next_token_begin:
	
	c = next_char();
	switch(token_type[c]) {
	case END_OF_FILE:
		token.type = END_OF_FILE;
		break;
	case NUMBER:
		value = 0;
		value = c - '0';
		for( ;; ) {
			c = next_char();
			if(token_type[c] != NUMBER) {
				ungetc(c, fin);
				break;
			}
			value = value * 10 + (c - '0');
		}
		token.value = value;
		token.type = NUMBER;
		break;
	case OPERATOR:
		token.value = c;
		token.type = OPERATOR;
		break;
	case SPACE:
		goto next_token_begin;
		break;
	case CHAR:
		buf[0] = c;
		for(i = 1;;) {
			c = next_char();
			if(token_type[c] != CHAR) {
				ungetc(c, fin);
				break;
			}
			buf[i++] = c;
		}
		buf[i] = '\0';
		strncpy(token.string, buf, 50);
		token.type = CHAR;
		break;
	default:
		token.type = UNSET;
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
	token_type['\r'] = SPACE;
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
	token_type[0] = END_OF_FILE;
	
	f_init_type = 1;
	
	return 0;
}

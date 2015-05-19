
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "compile.h"

char next_char(void);
Token next_token(void);
Token next_token_sub(void);
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
		} else if(token.type == UNSET) {
			fprintf(stderr, "Error\n");
			return -1;
		}
		
		switch(token.type) {
		case NUMBER:
			printf("number  : %d\n", token.value);
			break;
		case KEYWORD:
			printf("keyword : %s\n", token.string);
			break;
		case STRING:
			printf("string  : %s\n", token.string);
			break;
		case CHAR:
			printf("char    : %c\n", token.value);
			break;
		case SYMBOL:
			printf("symbol  : %s\n", token.string);
			break;
		case OPERATOR:
			printf("operator: %c\n", token.value);
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

Token next_token_sub(void)
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
		if(c == '\"') {
			for(i = 0;;) {
				c = next_char();
				if(c == '\"') break;
				buf[i++] = c;
			}
			buf[i] = '\0';
			strncpy(token.string, buf, 50);
			token.type = STRING;
		} else if(c == '\'') {
			c = next_char();
			if(c != '\\') {
				token.value = c;
			} else {
				c = next_char();
				token.value = c;
			}
			if(next_char() != '\'') {
				token.type = UNSET;
				return token;
			}
			token.type = CHAR;
		} else {
			token.value = c;
			token.type = OPERATOR;
		}
		break;
	case SPACE:
		goto next_token_begin;
		break;
	case SYMBOL:
		buf[0] = c;
		for(i = 1;;) {
			c = next_char();
			if(token_type[c] != SYMBOL) {
				ungetc(c, fin);
				break;
			}
			buf[i++] = c;
		}
		buf[i] = '\0';
		strncpy(token.string, buf, 50);
		token.type = SYMBOL;
		break;
	default:
		token.type = UNSET;
		break;
	}
	
	return token;
}

Token next_token(void) {
	Token token;
	
	token = next_token_sub();
	
	if(token.type == SYMBOL) {
		if(is_keyword(token.string)) {
			token.type = KEYWORD;
		} else {
			token.type = SYMBOL;
		}
	}
	
	return token;
}

#define KEYWORD				1
#define NO_KEYWORD			0
int is_keyword(char *word)
{
	/* Reserved keywords list for C language */
	char keywords[][20] = {
		"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
		"else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
		"return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
		"union", "unsigned", "void", "volatile", "while", "_Packed"
	};
	int i;
	int keywords_count = 33;
	
	for(i = 0; i < keywords_count; i++) {
		if(!strcmp(word, keywords[i]))
			return KEYWORD;
	}
	return NO_KEYWORD;
}

int init_token_type(void)
{
	int i;
	
	if(f_init_type == 1) return 0;
	
	for(i = 0; i < sizeof(token_type); i++) {
		token_type[i] = UNSET;
	}
	
	for(i = '0'; i <= '9'; i++) {
		token_type[i] = NUMBER;
	}
	
	for(i = 'a'; i <= 'z'; i++) {
		token_type[i] = SYMBOL;
	}
	
	for(i = 'A'; i <= 'Z'; i++) {
		token_type[i] = SYMBOL;
	}
	
	token_type['_'] = SYMBOL;
	
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "compile.h"

int expression(void);
int statement(void);
char next_char(void);
Token next_token(void);
Token next_token_sub(void);
int init_token_type(void);

int var_list_init(void);
int var_list_append(Variable var);
int var_list_exit(void);

/* global variable */
FILE *fin;
Variable_list var_list;
char f_fp; /* flag of file pointer */
char token_type[256];
char f_init_type;

int compile(FILE *fp)
{
	fin = fp;
	f_fp = 1;
	
	var_list_init();
	
	expression();
	
	var_list_exit();
	
	f_fp = 0;
	return 0;
}

int expression(void)
{
	int ret;
	
	for(;;) {
		ret = statement();
		
		if(ret == 1) return 0;
		else if(ret == -1) return -1;
	}
	
	return -1;
}

int statement(void)
{
	Token token, ntoken, nntoken, nnntoken;
	Variable variable;
	Node node;
	Function function;
	int i;
	
	for(;;) {
		token = next_token();
		if(token.type == END_OF_FILE) {
			return 1;
		} else if(token.type == UNSET) {
			fprintf(stderr, "Error\n");
			return -1;
		}
		
		switch(token.type) {
		case NUMBER:
			//printf("%d ", token.value);
			break;
		case KEYWORD:
			if(!strcmp(token.string, "int") || !strcmp(token.string, "void") || !strcmp(token.string, "short") ||
				!strcmp(token.string, "long") || !strcmp(token.string, "char") || !strcmp(token.string, "float") ||
				!strcmp(token.string, "double"))
			{
				ntoken = next_token();
				if(ntoken.type == SYMBOL) {
					nntoken = next_token();
					if(nntoken.type == OPERATOR && nntoken.value == '=') { /* with initilize */
						nnntoken = next_token();
						if(nnntoken.type == NUMBER) {
							variable.value = nnntoken.value;
							strncpy(variable.name, ntoken.string, 30);
							if(!strcmp(token.string, "int")) {
								variable.type = INT;
							} else if(!strcmp(token.string, "void")) {
								variable.type = VOID;
							} else if(!strcmp(token.string, "short")) {
								variable.type = SHORT;
							} else if(!strcmp(token.string, "long")) {
								variable.type = LONG;
							} else if(!strcmp(token.string, "char")) {
								variable.type = CHAR;
							} else if(!strcmp(token.string, "float")) {
								variable.type = FLOAT;
							} else if(!strcmp(token.string, "double")) {
								variable.type = DOUBLE;
							}
							
							var_list_append(variable);
						}
					} else if(nntoken.type == SPLIT && nntoken.value == ';') { /* only variable declaration */
						strncpy(variable.name, ntoken.string, 30);
						if(!strcmp(token.string, "int")) {
								variable.type = INT;
							} else if(!strcmp(token.string, "void")) {
								variable.type = VOID;
							} else if(!strcmp(token.string, "short")) {
								variable.type = SHORT;
							} else if(!strcmp(token.string, "long")) {
								variable.type = LONG;
							} else if(!strcmp(token.string, "char")) {
								variable.type = CHAR;
							} else if(!strcmp(token.string, "float")) {
								variable.type = FLOAT;
							} else if(!strcmp(token.string, "double")) {
								variable.type = DOUBLE;
							}
						variable.value = 0;
						
						var_list_append(variable);
					} else if(nntoken.type == SPLIT && nntoken.value == '(') { /* function */
						nnntoken = next_token();
						if(nnntoken.type != SPLIT && nnntoken.value != ')') { /* not prototype */
							strncpy(function.name, ntoken.string, 30);
							if(!strcmp(token.string, "int")) {
								function.type = INT;
							} else if(!strcmp(token.string, "void")) {
								function.type = VOID;
							} else if(!strcmp(token.string, "short")) {
								function.type = SHORT;
							} else if(!strcmp(token.string, "long")) {
								function.type = LONG;
							} else if(!strcmp(token.string, "char")) {
								function.type = CHAR;
							} else if(!strcmp(token.string, "float")) {
								function.type = FLOAT;
							} else if(!strcmp(token.string, "double")) {
								function.type = DOUBLE;
							}
						} else if((nnntoken = next_token()).type == SPLIT && nnntoken.value == ';') { /* prototype */
							strncpy(function.name, ntoken.string, 30);
							if(!strcmp(token.string, "int")) {
								function.type = INT;
							} else if(!strcmp(token.string, "void")) {
								function.type = VOID;
							} else if(!strcmp(token.string, "short")) {
								function.type = SHORT;
							} else if(!strcmp(token.string, "long")) {
								function.type = LONG;
							} else if(!strcmp(token.string, "char")) {
								function.type = CHAR;
							} else if(!strcmp(token.string, "float")) {
								function.type = FLOAT;
							} else if(!strcmp(token.string, "double")) {
								function.type = DOUBLE;
							}
						} else {
							fprintf(stderr, "function error\n");
							return -1;
						}
					}
				}
			} else if(!strcmp(token.string, "return")) {
				
			}
			//printf("%s ", token.string);
			break;
		case STRING:
			//printf("%s ", token.string);
			break;
		case CHAR:
			//printf("%c ", token.value);
			break;
		case SYMBOL:
			//printf("%s ", token.string);
			break;
		case OPERATOR:
			//printf("%c ", token.value);
			break;
		case SPLIT:
			if(token.value == ';') {
				return 0;
			}
			//printf("\n%c\n", token.value);
			break;
		default:
			printf("* ");
			break;
		}
	}
	
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
			if(token_type[c] != SYMBOL && token_type[c] != NUMBER) {
				ungetc(c, fin);
				break;
			}
			buf[i++] = c;
		}
		buf[i] = '\0';
		strncpy(token.string, buf, 50);
		token.type = SYMBOL;
		break;
	case SPLIT:
		token.value = c;
		token.type = SPLIT;
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

#define D_KEYWORD					1
#define D_NO_KEYWORD				0
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
			return D_KEYWORD;
	}
	return D_NO_KEYWORD;
}
#undef D_KEYWORD
#undef D_NO_KEYWORD

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
	token_type['('] = SPLIT;
	token_type[')'] = SPLIT;
	token_type['*'] = OPERATOR;
	token_type['+'] = OPERATOR;
	token_type[','] = SPLIT;
	token_type['-'] = OPERATOR;
	token_type['.'] = OPERATOR;
	token_type['/'] = OPERATOR;
	token_type['@'] = OPERATOR;
	token_type['['] = SPLIT;
	token_type[']'] = SPLIT;
	token_type['{'] = SPLIT;
	token_type['}'] = SPLIT;
	token_type['\\'] = OPERATOR;
	token_type['^'] = OPERATOR;
	token_type['`'] = OPERATOR;
	token_type['|'] = OPERATOR;
	token_type['~'] = OPERATOR;
	token_type['<'] = OPERATOR;
	token_type['>'] = OPERATOR;
	token_type[':'] = SPLIT;
	token_type[';'] = SPLIT;
	token_type['='] = OPERATOR;
	token_type['?'] = OPERATOR;
	token_type[0] = END_OF_FILE;
	
	f_init_type = 1;
	
	return 0;
}

int var_list_init(void)
{
	var_list.var[0] = NULL;
	var_list.count = 0;
	
	return 0;
}

int var_list_append(Variable var)
{
	Variable *v;
	
	v = (Variable *)malloc(sizeof(Variable));
	if(v == NULL) {
		fprintf(stderr, "memory allocate error\n");
		return -1;
	}
	
	*v = var;
	var_list.var[var_list.count] = v;
	
	var_list.count++;
	
	return var_list.count;
}

int var_list_exit(void)
{
	int i;
	
	for(i = 0; i < var_list.count; i++) {
		free(var_list.var[i]);
	}
	
	return 0;
}
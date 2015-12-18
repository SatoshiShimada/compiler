/*
 * PreProcessor for C
 *
 * functions
 * Delete define, include, ifdef, endif, ifndef, undef, else
 * Delete comments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum FLAG {
	F_CLEAR = 0,
	F_SET = 1,
};

int preprocessor(void)
{
	FILE *fin, *fout;
	char c, c_next;
	/* flag of line comment */
	char f_line_comment = F_CLEAR;
	/* flag of block comment */
	char f_block_comment = F_CLEAR;
	char buf[1024];

	fin = stdin;
	fout = stdout;

	while((c = fgetc(fin)) != EOF) {
		if(f_line_comment == F_SET) {
			if(c == '\n') {
				f_line_comment = F_CLEAR;
			} else {
				continue;
			}
		}
		if(f_block_comment == F_SET) {
			if(c == '*') {
				c_next = fgetc(fin);
				if(c_next == '/') {
					fputc(' ', fout);
					f_block_comment = F_CLEAR;
				}
			}
			continue;
		}
		if(c == '#') {
			fgets(buf, sizeof(buf), fin);
		} else if(c == '/') {
			c_next = fgetc(fin);
			if(c_next == '/') {
				f_line_comment = F_SET;
			} else if(c_next == '*') {
				f_block_comment = F_SET;
			} else {
				ungetc(c_next, fin);
				fputc(c, fout);
			}
		} else {
			fputc(c, fout);
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	return preprocessor();
}


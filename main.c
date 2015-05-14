
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compile.h"

int main(int argc, char **argv)
{
	FILE *fp;
	
	fp = fopen("test.txt", "r");
	if(!fp) {
		fprintf(stderr, "file open error\n");
		return -1;
	}
	
	compile();
	
	fclose(fp);
	return 0;
}

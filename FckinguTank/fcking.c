#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

void doubleword(char *name, FILE *fp);
int getword(FILE *fp, char *buf, int size);

int main(int argc, char *argv[])
{
	int i;
	FILE *fp;
	
	for(i = 1; i < argc; i++)
	{
		fp = fopen(argv[i], "r");
		if(fp == NULL)
		{
			fprintf(stderr, "%s: can't open '%s' (%s)\n",
				argv[0], argv[i], stderror(errno));
			return EXIT_FAILURE;
		}
		else
		{
			doubleword(argv[i], fp);
			fclose(fp);
		}
	}

	if(argc == 1)
		doubleword(NULL, stdin);

	return EXIT_SUCCESS;
}


void doubleword(char *name, FILE *fp)
{

}

int getword(FILE *fp, char *buf, int size)
{
	int c;
	int linenum = 0;
	
	c = getc(fp);
	for(; c != EOF && isspace(c); c = getc(fp))
		if(c == '\n')
			linenum++;


	if(c != EOF)
		ungetc(c, fp);

	return (buf[0] != '\0');
}


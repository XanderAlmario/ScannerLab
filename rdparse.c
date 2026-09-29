
/* this program computes sums based on the text file input */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "scan.h"

void parseerror(char *message)
{
   printf("Error: %s\n",message);
   exit(0);
}

struct token currenttoken;

void match(int tokenid)
{
	if (currenttoken.id == tokenid)
	{
		printf("match %s (%s)\n", tokennames[tokenid],currenttoken.lexeme);
		currenttoken = gettoken();
	}
	else
	{
		printf("error\n");
		currenttoken = gettoken();
	}
}

void E();

void S()
{
	if (currenttoken.id == TokenEndOfFile)
	{	
	}
	else
	{
		E(); S();
	}
}

void E()
{
	match(TokenNumber);
	if (currenttoken.id == TokenPlus)
	{
		match(TokenPlus);
		E();
	}
	else
	{
		match(TokenEquals);
	}
}

int main(int argc, char** argv)
{
   char filename[20];
   strcpy(filename,"test1.txt");
   if (argc >= 2)
      strcpy(filename,argv[1]);
   openfile(filename);
   currenttoken = gettoken();
   S();
   return 0;
}


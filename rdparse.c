
/* this program computes sums based on the text file input */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "scan.h"

int errorcount = 0;

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
		printf("Symbol expected: %s\n", tokennames[tokenid]);
		errorcount++;
		currenttoken = gettoken();
	}
}

void Prg();
void Blk();
void Stm();
void Argfollow();
void Arg();
void Iffollow();
void Exp();
void Trmfollow();
void Trm();
void Facfollow();
void Fac();
void Litfollow();
void Lit();
void Val();
void Cnd();
void Rel();

void Prg()
{
	Blk();
	match(TokenEndOfFile);
}

void Blk()
{
	if (currenttoken.id == TokenIdentifier || currenttoken.id == TokenPrint || currenttoken.id == TokenIf)
	{
		Stm();
		Blk();
	}
}

void Stm()
{
	if (currenttoken.id == TokenIdentifier)
	{
		match(TokenIdentifier);
		match(TokenAssign);
		Exp();
	}
	else if (currenttoken.id == TokenPrint)
	{
		match(TokenPrint);
		match(TokenLeftParen);
		Arg();
		Argfollow();
		match(TokenRightParen);
		match(TokenSemicolon);
		printf("Print Assignment Statement Recognized");
	}
	else if (currenttoken.id == TokenIf)
	{
		printf("If Statement Begins\n");
		match(TokenIf);
		Cnd();
		match(TokenColon);
		Blk();
		Iffollow();
		printf("If Statement Ends\n");
	}
	else{
		printf("Invalid Statement\n");
		errorcount++;
		currenttoken = gettoken();
	}
}

void Argfollow()
{
	if (currenttoken.id == TokenComma)
	{
		Arg();
		Argfollow();
	}
}

void Arg()
{
	if (currenttoken.id = TokenQuote)
		match(TokenQuote);
	else
		Exp();
}

void Iffollow()
{
	if (currenttoken.id == TokenEndif)
	{
		match(TokenEndif);
		match(TokenSemicolon);
	}
	else if (currenttoken.id == TokenElse)
	{
		match(TokenElse);
		Blk();
		match(TokenEndif);
		match(TokenSemicolon);
	}
	else
	{
		printf("Incomplete if Statement\n");
		errorcount++;
		currenttoken = gettoken();
	}
}

void Exp()
{
	Trm();
	Trmfollow();
}

void Trmfollow()
{
	if (currenttoken.id == TokenPlus)
	{
		match(TokenPlus);
		Trm();
		Trmfollow();
	}
	else if (currenttoken.id == TokenMinus)
	{
		match(TokenMinus);
		Trm();
		Trmfollow();
	}
}

void Trm()
{
	Fac();
	Facfollow();
}

void Facfollow()
{
	if (currenttoken.id == TokenMultiply)
	{
		match(TokenMultiply);
		Fac();
		Facfollow();
	}
	else if (currenttoken.id == TokenDivide)
	{
		match(TokenDivide);
		Fac();
		Facfollow();
	}
}

void Fac()
{
	Lit();
	Litfollow();
}

void Litfollow()
{
	if (currenttoken.id == TokenRaise)
	{
		match(TokenRaise);
		Lit();
		Litfollow();
	}
}

void Lit()
{
	if (currenttoken.id == TokenMinus)
	{
		match(TokenMinus);
		Val();
	}
	else
	{
		Val();
	}
}

void Val()
{
	if (currenttoken.id == TokenIdentifier)
		match(TokenIdentifier);
	else if (currenttoken.id == TokenNumber)
		match(TokenNumber);
	else if (currenttoken.id == TokenSqrt)
	{
		match(TokenSqrt);
		match(TokenLeftParen);
		Exp();
		match(TokenRightParen);
	}
	else
	{
		match(TokenLeftParen);
		Exp();
		match(TokenRightParen);
	}
}

void Cnd()
{
	Exp();
	Rel();
	Exp();
}

void Rel()
{
	if (currenttoken.id == TokenLT)
		match(TokenLT);
	else if (currenttoken.id == TokenEquals)
		match(TokenEquals);
	else if (currenttoken.id == TokenGT)
		match(TokenGT);
	else if (currenttoken.id == TokenGTE)
		match(TokenGTE);
	else if (currenttoken.id == TokenNE)
		match(TokenNE);
	else if (currenttoken.id == TokenLTE)
		match(TokenLTE);
	else
	{
		printf("Missing relational operator\n");
		errorcount++;
		currenttoken = gettoken();
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
	Prg();

	if (errorcount == 0)
		printf("%s is a valid SimpCalc program\n", filename);
	else
		printf("s is NOT a valid SimpCalc program (%d error(s))\n", filename, errorcount);
	
	return 0;
}


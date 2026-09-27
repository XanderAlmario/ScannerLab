
/* this program computes results based on the text file input */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "scan.h"

void parseerror(char *message)
{
   printf("Error: %s\n",message);
   exit(0);
}

int main(int argc, char** argv)
{
   char filename[20];
   struct token t;
   strcpy(filename,"test1.txt");
   if (argc >= 2)
      strcpy(filename,argv[1]);
   openfile(filename);
   t = gettoken();
   while (t.id != TokenEndOfFile)
   {
      int number;
      int result;
      int op;
      result = 0;
      if (t.id != TokenNumber)
         parseerror("Number expected");
      printf("%s\n",t.lexeme);
      sscanf(t.lexeme,"%d",&number);
      result = number;
      t = gettoken();
      while (t.id == TokenPlus || t.id == TokenMinus || t.id == TokenDivide)
      {

         switch (t.id) 
         {
            case TokenPlus:
               op = 11;
               break;
            case TokenMinus:
               op = 12;
               break;
            case TokenDivide:
               op = 13;
               break;
         }

         t = gettoken();

         if (t.id != TokenNumber)
            parseerror("Number expected");
         printf("%s\n",t.lexeme);
         sscanf(t.lexeme,"%d",&number);
         if (op == 11) result += number;
         else if (op == 12) result -= number;
         else if (op == 13)
         {
            if (number != 0) result /= number;
            else parseerror("cannot divide by 0");
         }
         t = gettoken();
      }
      if (t.id != TokenEquals)
         parseerror("== expected");
      printf("the result is: %d\n",result);
      t = gettoken();
   }
   return 0;
}



/* this program computes results based on the text file input */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>
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
         op = t.id;
         t = gettoken();

         if (t.id != TokenNumber)
            parseerror("Number expected");
         printf("%s\n",t.lexeme);
         sscanf(t.lexeme,"%d",&number);
         if (op == 3) result *= number;
         else if (op == 11) result += number;
         else if (op == 12) result -= number;
         else if (op == 13)
         {
            if (number != 0) result /= number;
            else if (number == 0) parseerror("cannot divide by 0");
         }
         else if (op == 15) result = pow(result, number);
         t = gettoken();
      }
      if (t.id != TokenEquals)
         parseerror("== expected");
      printf("the result is: %d\n",result);
      t = gettoken();
   }
   return 0;
}


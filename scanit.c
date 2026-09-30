
/* this program repeatedly calls gettoken() and prints id and lexeme */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "scan.h"

int main(int argc, char** argv)
{
   char filename[20];
   char keywords [8][6] = { "PRINT", "IF", "ELSE", "ENDIF", "SQRT", "AND", "OR", "NOT"};
   char printedKeywords [8][6] = { "Print", "If", "Else", "Endif", "Sqrt", "And", "Or", "Not"};
   strcpy(filename,"test1.txt");	
   if (argc >= 2)
      strcpy(filename,argv[1]);
   openfile(filename);
   struct token t = gettoken();
   while ( t.id != TokenEndOfFile )
   {
      if (t.id == 7)
      {
         bool notKeyword = true;
         for (int i = 0; i < 8; i++)
         {
            if (strcmp(t.lexeme, keywords[i]) == 0) 
            {
               printf("%s %s\n", printedKeywords[i], t.lexeme);
               notKeyword = false;
               break;
            }
         }
         if (notKeyword) printf("%s %s\n", tokennames[t.id], t.lexeme);
      }
      else if (t.id != 13) printf("%s %s\n", tokennames[t.id], t.lexeme);
      t = gettoken();
   }
   return 0;
}


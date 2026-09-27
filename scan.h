/* prototypes for the main functions of scan.c */

#include "token.h"
#define FALSE 0
#define TRUE 1
int openfile(char *filename);
struct token gettoken();
int getlinenumber();


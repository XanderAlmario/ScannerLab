
/* this module defines a gettoken() function      */
/* call openfile("filename") to set up the module */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scan.h"

/* character classes */
#define DIGIT        0
#define NEWLINE      1
#define SPACE        2
#define TAB          3
#define OTHER        4
#define PLUS         5
#define MINUS        6
#define DIVIDE       7
#define EQUAL        8
#define EOFCHAR      9
#define MULTIPLY    10
#define COLON       11
#define LT          12
#define GT          13
#define NotEqual    14
#define QUOTE       15
#define UNDERSCORE  16
#define LETTER      17
#define SEMICOLON   18
#define COMMA       19
#define LEFTPAREN   20
#define RIGHTPAREN  21
#define PERIOD      22
    
/* state transition table */
int delta[][23] = {
                
    /*          0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22*/
    /*  0 */ {  1,  0,  0,  0, 51, 21, 22, 23, 26, 29,  2,  3,  4,  5,  6,  7,  8,  8, 31, 32, 34, 35, 51 },
    /*  1 */ {  1, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 10 },
    /*  2 */ { 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 25, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43 },
    /*  3 */ { 42, 42, 42, 42, 42, 42, 42, 42, 33, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42 },
    /*  4 */ { 44, 44, 44, 44, 44, 44, 44, 44, 24, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44 },
    /*  5 */ { 45, 45, 45, 45, 45, 45, 45, 45, 27, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45 },
    /*  6 */ { 52, 52, 52, 52, 52, 52, 52, 52, 28, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52 },
    /*  7 */ {  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  9,  7,  7,  7,  7,  7,  7,  7 },
    /*  8 */ {  8, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,  8,  8, 47, 47, 47, 47, 47 },
    /*  9 */ { 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46 },
   /*  10 */ { 11, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51 },
   /*  11 */ { 11, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 51 }
};

#define MAXLINELEN 1000

FILE *file;
static int linenum = 1;
char line[MAXLINELEN];
int len = 0;
int ptr = 1;
int pushback = FALSE;
char charread = '\0';
    
int openfile(char *filename)
{
    file = fopen(filename,"r");
    if (file == NULL)
    {
       printf("File not found.");
       exit(1);
    }
    return 0;
}

char mygetchar()
{
    if (pushback)
    {
        pushback = FALSE;
    }
    else
    {
    	charread = fgetc(file);
    	if (charread == '\n')
    	   linenum++;
    }
    /*    printf("-->%d\n", charread); */
    return charread;

}
    
int getlinenumber()
{
    return linenum;
}
    
int charclass(char c)
{
    if ((c>='0') && (c<='9'))
        return DIGIT;
    else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return LETTER;
    switch(c)
    {
        case  '+': return PLUS;
        case '\r':
        case '\n': return NEWLINE;
        case  ' ': return SPACE;
        case '\t': return TAB;
        case  EOF: return EOFCHAR;
        case  '=': return EQUAL;
        case '-' : return MINUS;
        case '/' : return DIVIDE;
        case '*' : return MULTIPLY;
        case ':' : return COLON;
        case '<' : return LT;
        case '>' : return GT;
        case '!' : return NotEqual;
        case '"' : return QUOTE;
        case '_' : return UNDERSCORE;
        case ';' : return SEMICOLON;
        case ',' : return COMMA;
        case '(' : return LEFTPAREN;
        case ')' : return RIGHTPAREN;
        case '.' : return PERIOD;
        default  : return OTHER;
    }
}

const char *errormessage(int errnum)
{
    switch(errnum)
    {
        case 51: return "Illegal character";
        case 52: return "Unkown token";
        default: return "Unspecified error";
    }
}

struct token gettoken()
{
    int state = 0;
    struct token temp;

    strcpy(temp.lexeme,"");
    char placeholder[] = {'.','\0'}; /* single character string */
    while (state < 20)
    {
        char c = mygetchar();
        placeholder[0] = c;
        int ch = charclass(c);
        state = delta[state][ch];
        /* printf("class:"+ch+"("+c+") -> state "+ state); */
        if (state == 0)
        /* reset if brought back to state 0 (white spaces and comments) */
            strcpy(temp.lexeme,"");
        else if (state < 40) /* no pushback */
            strcat(temp.lexeme, placeholder);
    }
    if (state > 50) /* greater than 50 means error */
    {
        printf("Lexical Error: %s (line #%d)\n", errormessage(state), linenum);
        temp.id = 0; /* error token */
        strcpy(temp.lexeme,"");
    }
    else if (state >= 40) /* 40 plus means valid token with pushback */
    {
        temp.id = state % 10;
        pushback = TRUE;
    }
    else if (state >= 20) /* 20 plus means valid token with NO pushback */
    {
        temp.id = state - 10;
        pushback = FALSE;
    }
    
    return temp;
}


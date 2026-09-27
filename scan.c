
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
    
/* state transition table */
int delta[][10] = {
                
    /*          0,  1,  2,  3,  4,  5,  6,  7,  8,  9*/
    /*  0 */ {  1,  0,  0,  0, 41, 11, 12, 13, 16, 19},
    /*  1 */ {  1, 31, 31, 31, 31, 31, 31, 31, 31, 31}
    // /*  2 */ { 42, 42, 42, 42, 42, 13, 42, 42, 42,  0},
    ///*  3 */ {   }
    ///*  4 */ {   }
    ///*  5 */ {   }
    ///*  6 */ {   }
    ///*  7 */ {   }
    ///*  8 */ {   }

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
    switch(c)
    {
        case  '+': return PLUS;
        case '\r':
        case '\n': return NEWLINE;
        case  ' ': return SPACE;
        case '\t': return TAB;
        case  EOF: return EOFCHAR;
        case  '=': return EQUAL;
        case '-': return MINUS;
        case '/': return DIVIDE;
        // case '*': return MULTIPLY;
        // case '**': return RAISE;
        // case ',': return COMMA;
        // case ';': return SEMICOLON;
        // case ':=': return ASSIGN;
        // case '<=': return LTEQUAL;
        default  : return OTHER;
    }
}

const char *errormessage(int errnum)
{
    switch(errnum)
    {
        case 41: return "Illegal character";
        case 42: return "Use two equal signs";
        default: return "Unspecified error";
    }
}

struct token gettoken()
{
    int state = 0;
    struct token temp;

    strcpy(temp.lexeme,"");
    char placeholder[] = {'.','\0'}; /* single character string */
    while (state < 3)
    {
        char c = mygetchar();
        placeholder[0] = c;
        int ch = charclass(c);
        state = delta[state][ch];
        /* printf("class:"+ch+"("+c+") -> state "+ state); */
        if (state == 0)
        /* reset if brought back to state 0 (white spaces and comments) */
            strcpy(temp.lexeme,"");
        else if (state < 30) /* no pushback */
            strcat(temp.lexeme, placeholder);
    }
    if (state > 40) /* greater than 40 means error */
    {
        printf("Lexical Error: %s (line #%d)\n", errormessage(state), linenum);
        temp.id = 0; /* error token */
        strcpy(temp.lexeme,"");
    }
    else if (state >= 30) /* 20 plus means valid token with pushback */
    {
        temp.id = state % 10;
        pushback = TRUE;
    }
    else if (state >= 10) /* 10 plus means valid token with NO pushback */
    {
        // temp.id = state % 10;
        pushback = FALSE;
    }
    
    return temp;
}


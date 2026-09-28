
/* structure definition for tokens and #defines for token id constants */
 
struct token
{
	int id;
	char lexeme[1000];
};

extern const char *tokennames[]; /* contains token names for each token below */ 
/* constants representing valid token ids */
#define TokenNumber      1
#define TokenColon		 2
#define TokenMultiply	 3
#define TokenLT 		 4
#define TokenGT			 5
#define TokenQuote		 6
#define TokenIdentifier	 7
#define TokenPlus        11
#define TokenMinus  	 12
#define TokenDivide		 13
#define TokenLTE		 14
#define TokenRaise		 15
#define TokenEquals      16
#define TokenGTE		 17
#define TokenNE			 18
#define TokenEndOfFile	 19
#define TokenAssign 	 23

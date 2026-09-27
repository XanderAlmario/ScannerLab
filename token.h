
/* structure definition for tokens and #defines for token id constants */
 
struct token
{
	int id;
	char lexeme[1000];
};

extern const char *tokennames[]; /* contains token names for each token below */ 
/* constants representing valid token ids */
#define TokenNumber      1
#define TokenPlus        11
#define TokenMinus  	 12
#define TokenDivide		 13
#define TokenEquals      16
#define TokenEndOfFile	 19

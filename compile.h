
typedef enum {
	UNSET = 0,
	END_OF_FILE = 10,
	SPACE,
	NUMBER,
	OPERATOR,
	CHAR,
	STRING,
	SYMBOL,
	KEYWORD,
	SPLIT,
} Token_type;

typedef struct {
	int value;
	char string[50];
	Token_type type;
} Token;

int compile(FILE *);

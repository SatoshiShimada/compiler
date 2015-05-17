
typedef enum {
	UNSET,
	END_OF_FILE,
	NUMBER,
	OPERATOR,
	CHAR,
	STRING,
	SIGN
} Token_type;

typedef struct {
	int value;
	//int type;
	Token_type type;
} Token;

int compile(FILE *);
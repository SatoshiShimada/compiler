
typedef enum {
	UNSET = 0,
	END_OF_FILE = 10,
	NUMBER,
	OPERATOR,
	CHAR,
	SPACE,
	STRING,
	SIGN
} Token_type;

typedef struct {
	int value;
	char string[50];
	Token_type type;
} Token;

int compile(FILE *);


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

typedef enum {
	VOID,
	INT,
	CHAR,
	SHORT,
	LONG,
	FLOAT,
	DOUBLE
} Variable_type;

typedef struct {
	int value;
	char string[50];
	Token_type type;
} Token;

typedef struct {
	char name[30]; /* name of variable */
	int value;
	Variable_type type;
} Variable;

typedef struct node {
	int operator;
	Token_type type;
	int value;
	struct node *right, *left;
} Node;

int compile(FILE *);

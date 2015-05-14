
typedef struct {
	int value;
	//int type;
	enum {
		NUMBER,
		OPERATOR,
		CHAR,
		STRING,
		SIGN
	} type;
} Token;

int compile(void);
#ifndef __TOKEN_H___
#define __TOKEN_H___

typedef enum {
	Illegal,
	TokenEOF,
	Int,
	Assign,
	Plus,
	Minus,
	Asterisk,
	Slash,
	LParen,
	RParen,
	Circumflex, // ^
} TokenType;

typedef struct {
	TokenType type;
	char* literal;
} Token;

typedef struct Node {
	Token data;
	struct Node* next;
} TokenList;

void push_token(TokenList** head, Token data);

char* token_type(TokenType t);

void print_token_list(TokenList* t);

#endif

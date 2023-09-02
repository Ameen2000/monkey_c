#ifndef __TOKEN_H___
#define __TOKEN_H___

typedef enum {
	Illegal,
	TokenEOF,
	// Identifiers
	Ident,
	Int,
	// Operators
	Assign,
	Plus,
	Minus,
	Asterisk,
	Slash,
	// Delimeters
	Comma,
	SemiColon,
	LParen,
	RParen,
	LBrace,
	RBrace,
	// Other stuff
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

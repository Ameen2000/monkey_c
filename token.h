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
	EQ,
	Bang,
	NOT_EQ,
	// Delimeters
	Comma,
	SemiColon,
	LParen,
	RParen,
	LBrace,
	RBrace,
	// Keywords
	Function,
	Let,
	// Other stuff
	Circumflex, // ^
} TokenType;

typedef struct {
	TokenType type;
	char* literal;
} Token;

typedef struct TokenList {
	Token data;
	struct TokenList* next;
} TokenList;

TokenList* push_token(TokenList* head, Token data);

TokenList* list_reverse(TokenList* list);

char* token_type(TokenType t);

void print_token_list(TokenList* t);

TokenType lookup_ident(char* ident);

#endif

#ifndef __LEXER_H__
#define __LEXER_H__

#include "token.h"

typedef struct Lexer {
	char* input;
	int input_len;
	int position;
	int readPosition;
	char ch;
} Lexer;

Lexer* init(char* input);

TokenList* lex(char* input);

#endif

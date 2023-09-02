#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>
#include "lexer.h"
#include "token.h"

void read_char(Lexer *l);

Lexer* init(char* input) {
	Lexer* l;
	l = calloc(1, sizeof *l);
	if (l == NULL) {
		return NULL;
	}

	l->input = input;
	l->input_len = strlen(input);
	l->position = 0;
	l->readPosition = 1;
	l->ch = *input;
	return l;
}

void read_char(Lexer* l) {
	int len, readPosition;
	readPosition = l->readPosition;
	len = l->input_len;
	if (readPosition >= len) {
		l->ch = 0;
	} else {
		l->ch = l->input[l->readPosition];
	}
	l->position = l->readPosition;
	++l->readPosition;
}

char* read_number(Lexer* l) {
	size_t pos;
	uint8_t is;
	char* ret;
	pos = l->position;
	while ((is = isdigit(l->ch))) {
		read_char(l);
		is = isdigit(l->ch);
	}
	ret = calloc((l->position - pos) + 1, sizeof *ret);
	if (ret == NULL) {
		return NULL;
	}
	memcpy(ret, l->input + pos, l->position - pos);
	l->position--;
	l->readPosition--;
	return ret;
}

char* read_identifier(Lexer* l) {
	size_t pos;
	uint8_t is;
	char* ret;
	pos = l->position;
	while ((is = (isalpha(l->ch) || (l->ch == '_')))) {
		read_char(l);
		is = (isalpha(l->ch) || (l->ch == '_'));
	}
	ret = calloc((l->position - pos) + 1, sizeof *ret);
	if (ret == NULL) {
		return NULL;
	}
	memcpy(ret, l->input + pos, l->position - pos);
	l->position--;
	l->readPosition--;
	return ret;
}

Token next_token(Lexer* l){
	Token tok;
	switch (l->ch) {
		case '=':
			tok.type = Assign;
			tok.literal = "=";
		case '+':
			tok.type = Plus;
			tok.literal = "+";
		case '-':
			tok.type = Minus;
			tok.literal = "-";
		case '*':
			tok.type = Asterisk;
			tok.literal = "*";
		case '/':
			tok.type = Slash;
			tok.literal = "/";
		case '^':
			tok.type = Circumflex;
			tok.literal = "^";
		case ',':
			tok.type = Comma;
			tok.literal = ",";
		case ';':
			tok.type = SemiColon;
			tok.literal = ";";
		case '{':
			tok.type = LBrace;
			tok.literal = "{";
		case '}':
			tok.type = RBrace;
			tok.literal = "}";
		case '(':
			tok.type = LParen;
			tok.literal = "(";
		case ')':
			tok.type = RParen;
			tok.literal = ")";
		case '\0':
			tok.type = TokenEOF;
			tok.literal = "";
		default:
			if (isdigit(l->ch)) {
				tok.type = Int;
				tok.literal = read_number(l);
			} else if (isalpha(l->ch)) {
				tok.type = Ident;
				tok.literal = read_number(l);
			} else {
				tok.type = Illegal;
				tok.literal = "";
		}

	}
	read_char(l);
	return tok;
}

TokenList* lex(char* string) {
	Lexer* lexer = init(string);
	TokenList* head = (TokenList*) malloc(sizeof(TokenList));
	while (lexer->ch != '\0') {
		Token tok = next_token(lexer);
		TokenList** head_ptr = &head;
	}
	return head;
}

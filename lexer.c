#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>
#include "lexer.h"
#include "token.h"

void lexer_read_char(Lexer *l);

Lexer* init(char* input) {
	Lexer* l;
	l = calloc(1, sizeof *l);
	if (l == NULL) {
		return NULL;
	}

	l->input = input;
	l->input_len = strlen(input);
	l->position = 0;
	l->read_position = 1;
	l->ch = *input;
	return l;
}

void lexer_read_char(Lexer* l) {
	int len, readPosition;
	readPosition = l->read_position;
	len = l->input_len;
	if (readPosition >= len) {
		l->ch = 0;
	} else {
		l->ch = l->input[l->read_position];
	}
	l->position = l->read_position;
	++l->read_position;
}

char* read_number(Lexer* l) {
	size_t pos;
	uint8_t is;
	char* ret;
	pos = l->position;
	while ((is = isdigit(l->ch))) {
		lexer_read_char(l);
		is = isdigit(l->ch);
	}
	ret = calloc((l->position - pos) + 1, sizeof *ret);
	if (ret == NULL) {
		return NULL;
	}
	memcpy(ret, l->input + pos, l->position - pos);
	l->position--;
	l->read_position--;
	return ret;
}

uint8_t is_letter(char ch) {
	return ((('a' <= ch) && (ch <= 'z')) || (('A' <= ch) && (ch <= 'Z')) || (ch == '_')) ? 1 : 0;
}

char* read_identifier(Lexer* l) {
	size_t pos;
	uint8_t is;
	char* ret;
	pos = l->position;
	while ((is = is_letter(l->ch))) {
		lexer_read_char(l);
		is = (isalpha(l->ch) || (l->ch == '_'));
	}
	ret = calloc((l->position - pos) + 1, sizeof *ret);
	if (ret == NULL) {
		return NULL;
	}
	memcpy(ret, l->input + pos, l->position - pos);
	l->position--;
	l->read_position--;
	return ret;
}

void skip_white_space(Lexer* l) {
	while ((l->ch == ' ') || (l->ch == '\t') || (l->ch == '\n') || (l->ch == '\r')) {
		lexer_read_char(l);
	}
}

char peek_char(Lexer* l) {
	if (l->read_position >= l->input_len) {
		return 0;
	}
	return l->input[l->read_position];
}

Token next_token(Lexer* l){
	Token tok;
	skip_white_space(l);
	switch (l->ch) {
		case '=':
			if (peek_char(l) == '=') {
				tok.type = EQ;
				tok.literal = "==";
				lexer_read_char(l);
				lexer_read_char(l);
				return tok;
			} else {
				tok.type = Assign;
				tok.literal = "=";
				lexer_read_char(l);
				return tok;

			}
		case '+':
			tok.type = Plus;
			tok.literal = "+";
			lexer_read_char(l);
			return tok;
		case '-':
			tok.type = Minus;
			tok.literal = "-";
			lexer_read_char(l);
			return tok;
		case '*':
			tok.type = Asterisk;
			tok.literal = "*";
			lexer_read_char(l);
			return tok;
		case '/':
			tok.type = Slash;
			tok.literal = "/";
			lexer_read_char(l);
			return tok;
		case '!':
			if (peek_char(l) == '=') {
				tok.type = NOT_EQ;
				tok.literal = "!=";
				lexer_read_char(l);
				lexer_read_char(l);
				return tok;
			}
			else {
				tok.type = Bang;
				tok.literal = "!";
				lexer_read_char(l);
				return tok;
			}
		case '^':
			tok.type = Circumflex;
			tok.literal = "^";
			lexer_read_char(l);
			return tok;
		case ',':
			tok.type = Comma;
			tok.literal = ",";
			lexer_read_char(l);
			return tok;
		case ';':
			tok.type = SemiColon;
			tok.literal = ";";
			lexer_read_char(l);
			return tok;
		case '{':
			tok.type = LBrace;
			tok.literal = "{";
			lexer_read_char(l);
			return tok;
		case '}':
			tok.type = RBrace;
			tok.literal = "}";
			lexer_read_char(l);
			return tok;
		case '(':
			tok.type = LParen;
			tok.literal = "(";
			lexer_read_char(l);
			return tok;
		case ')':
			tok.type = RParen;
			tok.literal = ")";
			lexer_read_char(l);
			return tok;
		case '\0':
			tok.type = TokenEOF;
			tok.literal = "";
			lexer_read_char(l);
			return tok;
		default:
			if (isdigit(l->ch)) {
				tok.type = Int;
				tok.literal = read_number(l);
				lexer_read_char(l);
				return tok;
			} else if (is_letter(l->ch)) {
				tok.literal = read_identifier(l);
				tok.type = lookup_ident(tok.literal);
				lexer_read_char(l);
				return tok;
			} else {
				tok.type = Illegal;
				tok.literal = "";
				lexer_read_char(l);
				return tok;
		}

	}
}

TokenList* lex(char* input) {
	Lexer* lexer_ptr = init(input);
	Token tok = next_token(lexer_ptr);
	TokenList* accum = malloc(sizeof(TokenList));
	accum = NULL;
	while (strcmp(tok.literal, "") != 0) {
		accum = push_token(accum, tok);
		tok = next_token(lexer_ptr);
	}
	return list_reverse(accum);
}

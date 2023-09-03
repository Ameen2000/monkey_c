#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/_types/_null.h>
#include "token.h"

void push_token(TokenList* list, Token data) {
	TokenList new_head;
	new_head.data = data;
	new_head.next = list;
}

char* token_type(TokenType t) {
	switch (t) {
		case Illegal: return "Illegal";
		case TokenEOF: return "TokenEOF";
		case Assign: return "Assign";
		case Plus: return "Plus";
		case Minus: return "Minus";
		case Asterisk: return "Asterisk";
		case Slash: return "Slash";
		case Int: return "Int";
		case LParen: return "LParen";
		case RParen: return "RParen";
		case Circumflex: return "Circumflex";
		case Ident: return "Ident";
		case SemiColon: return "SemiColon";
		case LBrace: return "LBrace";
		case RBrace: return "RBrace";
		case Comma: return "Comma";
		case Function: return "Function";
		case Let: return "Let";
		case EQ: return "EQ";
		case NOT_EQ: return "NOT_EQ";
		case Bang: return "Bang";
	}
	return "";
}

TokenType lookup_ident(char* ident) {
	TokenType tok;
	if (strcmp(ident, "fn")) {
		tok = Function;
	} else if (strcmp(ident, "let")) {
		tok = Let;
	} else {
		tok = Ident;
	}
	return tok;
}

void print_token_list(TokenList* t) {
	while (t != NULL) {
		char* str = token_type(t->data.type);
		printf("%s\n", str);
		t = t->next;
	}
	printf("\n");
}

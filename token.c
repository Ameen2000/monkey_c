#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/_types/_null.h>
#include "token.h"

TokenList* push_token(TokenList* list, Token data) {
	TokenList* new = NULL;
	if (list == NULL) {
		new = malloc(sizeof(TokenList));
		if (new == NULL) {
			return NULL;
		}
		new->data = data;
		list = new;
		new->next = NULL;
	} else {
		new = malloc(sizeof(TokenList));
		if (new == NULL) {
			return NULL;
		}
		new->data = data;
		new->next = list;
		list = new;
	}
	return new;
}

TokenList* list_reverse(TokenList* list) {
	TokenList* prev = NULL;
	TokenList* curr = list;
	TokenList* next = NULL;
	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	list = prev;
	return list;
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
		case LT: return "LT";
		case GT: return "GT";
		case LTE: return "LTE";
		case GTE: return "GTE";
	}
	return "";
}

TokenType lookup_ident(char* ident) {
	TokenType tok;
	if (strcmp(ident, "fn") == 0) {
		tok = Function;
	} else if (strcmp(ident, "let") == 0) {
		tok = Let;
	} else {
		tok = Ident;
	}
	return tok;
}

void print_token_list(TokenList* t) {
	while (t != NULL) {
		char* str = t->data.literal;
		printf("%s : %s\n", token_type(t->data.type),str);
		t = t->next;
	}
	printf("\n");
}

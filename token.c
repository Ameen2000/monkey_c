#include <stdlib.h>
#include <stdio.h>
#include <sys/_types/_null.h>
#include "token.h"

void push_token(TokenList** head, Token data) {
	TokenList* new_node = (TokenList*) malloc(sizeof(TokenList));
	new_node->data = data;
	new_node->next = *head;
	*head = new_node;
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
	}
	return "";
}

void print_token_list(TokenList* t) {
	while (t != NULL) {
		char* str = token_type(t->data.type);
		printf("%s\n", str);
		t = t->next;
	}
	printf("\n");
}

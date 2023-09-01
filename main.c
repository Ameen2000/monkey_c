#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"

int main() {
	TokenList* l = lex("5 + 4 = 9");
	print_token_list(l);
}

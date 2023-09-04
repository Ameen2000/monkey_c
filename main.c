#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"

int main() {
	TokenList* l = lex("let x = 516 + 4 1 2 4 2");
	print_token_list(l);
}

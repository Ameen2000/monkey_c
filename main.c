#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"

int main() {
	TokenList* l = lex("let x = 5 + 4");
	print_token_list(l);
}

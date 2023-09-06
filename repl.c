#include "lexer.h"
#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT \
    fprintf(stdout, ">> "); \
    fflush(stdout);

const char* exit_prompt = "#quit\n";

void start() {
	char* buffer;
	size_t buffsize = 32;
	size_t user_input;
	buffer = malloc(buffsize * sizeof(char));
	int x = 1;
	while (x > 0) {
		PROMPT;
		user_input = getline(&buffer, &buffsize, stdin);
		if (strcmp(buffer,exit_prompt) == 0) {
			x = 0;
		}
		print_token_list(lex(buffer));
	}
}

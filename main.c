#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "helpers.h"
#include "types.h"
#include "vector.h"
#include "letter_lexem_parser.h"
#include "number_lexem_parser.h"
#include "operator_lexem_parser.h"

Lexem* read_next_lexem(FILE* file) {
    skip_white_character(file);
    int symbol = fpeek(file);
    Lexem* lexem;

    if(symbol == EOF) {
        return NULL;
    }

    if(isalpha(symbol) || symbol == '_') {
        lexem = read_letter_lexem(file);
    } else if(isdigit(symbol)) {
        lexem = read_number_lexem(file);
    } else {
        lexem = read_operator_lexem(file);
    }
    if(lexem->type == FAILED) {
        read_until_white_character(file, lexem->name);
    }

    return lexem;
}

LexemVector* lexer_analize(FILE* file) {
    LexemVector* tokens = create_vector();
    Lexem* lexem = read_next_lexem(file);
    while (lexem != NULL)
    {
        add_to_vector(tokens, lexem);
        lexem = read_next_lexem(file);
    }

    return tokens;
}

void print_tokens(LexemVector* tokens) {
    printf("[Name, Type]\n");
    for(int i = 0; i < tokens->size; i++) {
        if(tokens->data[i]->type == NEW_LINE) {
            printf("[\\n, %s]\n", from_lexem_type_to_string(tokens->data[i]->type));
            continue;
        }
        printf("[%s, %s]\n", tokens->data[i]->name, from_lexem_type_to_string(tokens->data[i]->type));
    }
}

int main(int argc, char *argv[]) {
    initialize_operator_lexem_parser();
    FILE* file = fopen(argv[1], "r");
    LexemVector* tokens = lexer_analize(file);
    print_tokens(tokens);
    return 0;
}
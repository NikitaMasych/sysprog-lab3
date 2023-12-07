#include "letter_lexem_parser.h"
#include "helpers.h"
#include <ctype.h>
#include <string.h>


int accepted_letter(char c) {
    return isalpha(c) || isdigit(c) || c == '_';
}


static Lexem reserved_lexems[] = {
    {"break", RESERVED_BREAK},
    {"case", RESERVED_CASE},
    {"catch", RESERVED_CATCH},
    {"class", RESERVED_CLASS},
    {"const", RESERVED_CONST},
    {"continue", RESERVED_CONTINUE},
    {"debugger", RESERVED_DEBUGGER},
    {"default", RESERVED_DEFAULT},
    {"delete", RESERVED_DELETE},
    {"do", RESERVED_DO},
    {"else", RESERVED_ELSE},
    {"export", RESERVED_EXPORT},
    {"extends", RESERVED_EXTENDS},
    {"false", RESERVED_FALSE},
    {"finally", RESERVED_FINALLY},
    {"for", RESERVED_FOR},
    {"function", RESERVED_FUNCTION},
    {"if", RESERVED_IF},
    {"import", RESERVED_IMPORT},
    {"in", RESERVED_IN},
    {"instanceof", RESERVED_INSTANCEOF},
    {"new", RESERVED_NEW},
    {"null", RESERVED_NULL},
    {"return", RESERVED_RETURN},
    {"super", RESERVED_SUPER},
    {"switch", RESERVED_SWITCH},
    {"this", RESERVED_THIS},
    {"throw", RESERVED_THROW},
    {"true", RESERVED_TRUE},
    {"try", RESERVED_TRY},
    {"typeof", RESERVED_TYPEOF},
    {"var", RESERVED_VAR},
    {"void", RESERVED_VOID},
    {"while", RESERVED_WHILE},
    {"with", RESERVED_WITH},
    {"let", RESERVED_LET},
    {"static", RESERVED_STATIC},
    {"yield", RESERVED_YIELD},
    {"await", RESERVED_AWAIT},
    {"reserved words", RESERVED_WORDS}
};


LexemType check_reserved_word(char* str) {
    int counter = 0;
    while(reserved_lexems[counter].type != RESERVED_WORDS) {
        if(strcmp(str, reserved_lexems[counter].name) == 0) {
            return reserved_lexems[counter].type;
        }
        counter++;
    }

    return FAILED;
}

Lexem* read_letter_lexem(FILE* file) {
    char c = fpeek(file);
    Lexem* lexem = empty_lexem();

    while(accepted_letter(c)) {
        fgetc(file);
        add_letter_to_str(lexem->name, c);
        c = fpeek(file);
    }

    lexem->type = check_reserved_word(lexem->name);
    if(lexem->type == FAILED) {
        lexem->type = IDENTIFIER;
    }

    return lexem;
}


#include "number_lexem_parser.h"
#include "helpers.h"
#include <ctype.h>

typedef enum {
    INITIAL,
    MAYBE_HEX_OR_FLOAT,
    HEX_PREFIX,
    DECIMAL,
    HEX,
    FLOAT,
    FINISH_STATES,
    F_DECIMAL,
    F_HEX,
    F_FLOAT,
    F_FAILED
} NumbericLexemState;


Lexem* read_number_lexem(FILE* file) {
    int c;
    NumbericLexemState state = INITIAL;
    Lexem* lexem = empty_lexem();

    while (1)
    {
        c = fpeek(file);
        switch (state)
        {
        case INITIAL:
            if(c == '0') {
                state = MAYBE_HEX_OR_FLOAT;
            } else if(isdigit(c)) {
                state = DECIMAL;
            } else {
                state = F_FAILED;
            }
            break;
        case MAYBE_HEX_OR_FLOAT:
            if(c == 'x' || c == 'X') {
                state = HEX_PREFIX;
            } else if(c == '.') {
                state = FLOAT;
            } else if (!isalpha(c)) {
                state = F_DECIMAL;
            } else {
                state = F_FAILED;
            }
            break;    
        case DECIMAL:
            if(isdigit(c)) {
                break;
            }
            if(c == '.') {
                state = FLOAT;
            } else if(!isalpha(c)) {
                state = F_DECIMAL;
            } else {
                state = F_FAILED;
            }
            break;
        case FLOAT:
            if(isdigit(c)) {
                break;
            }
            if(!isalpha(c)) {
                state = F_FLOAT;
            } else {
                state = F_FAILED;
            }
            break;
        case HEX_PREFIX:
            if(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' 
            || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F'
            || isdigit(c)) {
                state = HEX;
                break;
            }
            state = F_FAILED;
            break;
        case HEX:
            if(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' 
            || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F'
            || isdigit(c)) {
                break;
            }
            if(!isalpha(c)) {
                state = F_HEX;
            } else {
                state = F_FAILED;
            }
            break;
        default:
            return NULL;

        }
        if(state > FINISH_STATES) {
            break;
        }
        add_letter_to_str(lexem->name, c);
        fgetc(file);
    }

    if(state == F_HEX) {
        lexem->type = NUMERIC_LITERAL_HEX;
    } else if (state == F_DECIMAL) {
        lexem->type = NUMERIC_LITERAL_DECIMAL;
    } else if(state == F_FLOAT) {
        lexem->type = NUMERIC_LITERAL_FLOAT;
    } else {
        lexem->type = FAILED;
    }

    return lexem;
}

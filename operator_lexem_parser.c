#include "operator_lexem_parser.h"
#include "helpers.h"
#include <stdlib.h>

typedef enum {
    INITIAL,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    EXPONENT,
    ASSIGN,
    MODULUS,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    AND,
    OR,
    NOT,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    ONE_LINE_COMMENT,
    EMPTY,
    FINISH_STATES,
    F_STRONG_NOT_EQUAL,
    F_STRONG_EQUAL,
    F_INCREMENT,
    F_DECREMENT,
    F_ADD_ASSIGN,
    F_SUB_ASSIGN,
    F_MUL_ASSIGN,
    F_DIV_ASSIGN,
    F_MOD_ASSIGN,
    F_EXP_ASSIGN,
    F_GREATER_EQUAL,
    F_LESS_EQUAL,
    F_TERNARY,
    F_LOGICAL_AND,
    F_LOGICAL_OR,
    F_LEFT_SHIFT,
    F_RIGHT_SHIFT,
    F_PLUS,
    F_MINUS,
    F_DIVIDE,
    F_MULTIPLY,
    F_EXPONENT,
    F_ASSIGN,
    F_MODULUS,
    F_EQUAL,
    F_NOT_EQUAL,
    F_GREATER,
    F_LESS,
    F_AND,
    F_OR,
    F_NOT,
    F_POINT,
    F_ARROW,
    F_NEW_LINE,
    F_ROUND_LEFT_BRACKET,
    F_ROUND_RIGHT_BRACKET,
    F_SQUARE_LEFT_BRACKET,
    F_SQUARE_RIGHT_BRACKET,
    F_FIGURE_LEFT_BRACKET,
    F_FIGURE_RIGHT_BRACKET,
    F_SINGLE_STRING_LITERAL,
    F_DOUBLE_STRING_LITERAL,
    F_COLON,
    F_SEMICOLON,
    F_ONELINE_COMMENT,
    F_FAILED,
} OperatorLexemState;

static int char_initial_state[256];
static int final_lexem_type[256];

void initialize_operator_lexem_parser() {
    char_initial_state['+'] = PLUS;
    char_initial_state['-'] = MINUS;
    char_initial_state['/'] = DIVIDE;
    char_initial_state['*'] = MULTIPLY;
    char_initial_state['='] = ASSIGN;
    char_initial_state['%'] = MODULUS;
    char_initial_state['>'] = GREATER;
    char_initial_state['<'] = LESS;
    char_initial_state['&'] = AND;
    char_initial_state['|'] = OR;
    char_initial_state['!'] = NOT;
    char_initial_state['.'] = F_POINT;
    char_initial_state['\n'] = F_NEW_LINE;
    char_initial_state['('] = F_ROUND_LEFT_BRACKET;
    char_initial_state[')'] = F_ROUND_RIGHT_BRACKET;
    char_initial_state['['] = F_SQUARE_LEFT_BRACKET;
    char_initial_state[']'] = F_SQUARE_RIGHT_BRACKET;
    char_initial_state['{'] = F_FIGURE_LEFT_BRACKET;
    char_initial_state['}'] = F_FIGURE_RIGHT_BRACKET;
    char_initial_state['\''] = SINGLE_QUOTE;
    char_initial_state['"'] = DOUBLE_QUOTE;
    char_initial_state[':'] = F_COLON;
    char_initial_state[';'] = F_SEMICOLON;

    final_lexem_type[F_STRONG_NOT_EQUAL] = OPERATOR_STRONG_NOT_EQUAL;
    final_lexem_type[F_STRONG_EQUAL] = OPERATOR_STRONG_EQUAL;
    final_lexem_type[F_INCREMENT] = OPERATOR_INCREMENT;
    final_lexem_type[F_DECREMENT] = OPERATOR_DECREMENT;
    final_lexem_type[F_ADD_ASSIGN] = OPERATOR_ADD_ASSIGN;
    final_lexem_type[F_SUB_ASSIGN] = OPERATOR_SUB_ASSIGN;
    final_lexem_type[F_MUL_ASSIGN] = OPERATOR_MUL_ASSIGN;
    final_lexem_type[F_DIV_ASSIGN] = OPERATOR_DIV_ASSIGN;
    final_lexem_type[F_MOD_ASSIGN] = OPERATOR_MOD_ASSIGN;
    final_lexem_type[F_EXP_ASSIGN] = OPERATOR_EXP_ASSIGN;
    final_lexem_type[F_GREATER_EQUAL] = OPERATOR_GREATER_EQUAL;
    final_lexem_type[F_LESS_EQUAL] = OPERATOR_LESS_EQUAL;
    final_lexem_type[F_LOGICAL_AND] = OPERATOR_LOGICAL_AND;
    final_lexem_type[F_LOGICAL_OR] = OPERATOR_LOGICAL_OR;
    final_lexem_type[F_LEFT_SHIFT] = OPERATOR_LEFT_SHIFT;
    final_lexem_type[F_RIGHT_SHIFT] = OPERATOR_RIGHT_SHIFT;
    final_lexem_type[F_PLUS] = OPERATOR_PLUS;
    final_lexem_type[F_MINUS] = OPERATOR_MINUS;
    final_lexem_type[F_DIVIDE] = OPERATOR_DIVIDE;
    final_lexem_type[F_MULTIPLY] = OPERATOR_MULTIPLY;
    final_lexem_type[F_EXPONENT] = OPERATOR_EXPONENT;
    final_lexem_type[F_ASSIGN] = OPERATOR_ASSIGN;
    final_lexem_type[F_MODULUS] = OPERATOR_MODULUS;
    final_lexem_type[F_EQUAL] = OPERATOR_EQUAL;
    final_lexem_type[F_NOT_EQUAL] = OPERATOR_NOT_EQUAL;
    final_lexem_type[F_GREATER] = OPERATOR_GREATER;
    final_lexem_type[F_LESS] = OPERATOR_LESS;
    final_lexem_type[F_AND] = OPERATOR_AND;
    final_lexem_type[F_OR] = OPERATOR_OR;
    final_lexem_type[F_NOT] = OPERATOR_LOGICAL_NOT;
    final_lexem_type[F_FAILED] = FAILED;
    final_lexem_type[F_POINT] = POINT;
    final_lexem_type[F_ARROW] = ARROW;
    final_lexem_type[F_NEW_LINE] = NEW_LINE;
    final_lexem_type[F_ROUND_LEFT_BRACKET] = ROUND_LEFT_BRACKET;
    final_lexem_type[F_ROUND_RIGHT_BRACKET] = ROUND_RIGHT_BRACKET;
    final_lexem_type[F_SQUARE_LEFT_BRACKET] = SQUARE_LEFT_BRACKET;
    final_lexem_type[F_SQUARE_RIGHT_BRACKET] = SQUARE_RIGHT_BRACKET;
    final_lexem_type[F_FIGURE_LEFT_BRACKET] = FIGURE_LEFT_BRACKET;
    final_lexem_type[F_FIGURE_RIGHT_BRACKET] = FIGURE_RIGHT_BRACKET;
    final_lexem_type[F_SINGLE_STRING_LITERAL] = SINGLE_STRING_LITERAL;
    final_lexem_type[F_DOUBLE_STRING_LITERAL] = DOUBLE_STRING_LITERAL;
    final_lexem_type[F_COLON] = COLON;
    final_lexem_type[F_SEMICOLON] = SEMICOLON;
    final_lexem_type[F_ONELINE_COMMENT] = ONELINE_COMMENT;
}

void advance(FILE* file, Lexem* lexem, char c) {
    add_letter_to_str(lexem->name, c);
    fgetc(file);
}

#define ADVANCE advance(file, lexem, c)

Lexem* read_operator_lexem(FILE* file) {
    int c;
    OperatorLexemState state = INITIAL;
    Lexem* lexem = empty_lexem();
    while (1)
    {
        c = fpeek(file);
        OperatorLexemState tmp_state = char_initial_state[c];
        if(c == EOF) {
            tmp_state = EMPTY;
        }

        switch (state)
        {
        case INITIAL:
            state = tmp_state;
            if(state == 0) {
                state = F_FAILED;
            }
            switch (state)
            {
            case F_POINT:
            case F_NEW_LINE:
            case F_ROUND_LEFT_BRACKET:
            case F_ROUND_RIGHT_BRACKET:
            case F_SQUARE_LEFT_BRACKET:
            case F_SQUARE_RIGHT_BRACKET:
            case F_FIGURE_LEFT_BRACKET:
            case F_FIGURE_RIGHT_BRACKET:
            case F_COLON:
            case F_SEMICOLON:
                ADVANCE;
            }

            if(tmp_state == EMPTY) {
                state = F_FAILED; 
            }
            break;
        case PLUS:
            switch (tmp_state) {
            case PLUS: state = F_INCREMENT; ADVANCE; break;
            case ASSIGN: state = F_ADD_ASSIGN; ADVANCE; break;
            default: state = F_PLUS; break; }
            break;
        case MINUS:
            switch (tmp_state) {
            case MINUS: state = F_DECREMENT; ADVANCE; break;
            case ASSIGN: state = F_SUB_ASSIGN; ADVANCE; break;
            case GREATER: state = F_ARROW; ADVANCE; break;
            default: state = F_MINUS; break; }
            break;
        case DIVIDE:
            switch (tmp_state) {
            case ASSIGN: state = F_DIV_ASSIGN; ADVANCE; break;
            case DIVIDE: state = ONE_LINE_COMMENT; break;
            default: state = F_DIVIDE; break; }
            break;
        case MULTIPLY:
            switch (tmp_state) {
            case ASSIGN: state = F_MUL_ASSIGN; ADVANCE; break;
            case MULTIPLY: state = EXPONENT; break;
            default: state = F_MULTIPLY; break; }
            break;
        case EXPONENT:
            switch (tmp_state) {
            case ASSIGN: state = F_EXP_ASSIGN; ADVANCE; break;
            default: state = F_EXPONENT; break; }
            break;
        case MODULUS:
            switch (tmp_state) {
            case ASSIGN: state = F_MOD_ASSIGN; ADVANCE; break;
            default: state = F_MODULUS; break; }
            break;
        case ASSIGN:
            switch (tmp_state) {
            case ASSIGN: state = EQUAL; break;
            default: state = F_ASSIGN; break; }
            break;
        case EQUAL:
            switch (tmp_state) {
            case ASSIGN: state = F_STRONG_EQUAL; ADVANCE; break;
            default: state = F_EQUAL; break; }
            break;
        case NOT:
            switch (tmp_state) {
            case EQUAL: state = NOT_EQUAL; break;
            default: state = F_NOT; break; }
            break;
        case NOT_EQUAL:
            switch (tmp_state) {
            case ASSIGN: state = F_STRONG_NOT_EQUAL; ADVANCE; break;
            default: state = F_NOT_EQUAL; break; }
            break;
        case GREATER:
            switch (tmp_state) {
            case ASSIGN: state = F_GREATER_EQUAL; ADVANCE; break;
            case GREATER: state = F_RIGHT_SHIFT; ADVANCE; break;
            default: state = F_GREATER; break; }
            break;
        case LESS:
            switch (tmp_state) {
            case ASSIGN: state = F_LESS_EQUAL; ADVANCE; break;
            case LESS: state = F_LEFT_SHIFT; ADVANCE; break;
            default: state = F_LESS; break; }
            break;
        case AND:
            switch (tmp_state) {
            case AND: state = F_LOGICAL_AND; ADVANCE; break;
            default: state = F_AND; break; }
            break;
        case OR:
            switch (tmp_state) {
            case OR: state = F_LOGICAL_OR; ADVANCE; break;
            default: state = F_OR; break; }
            break;
        case SINGLE_QUOTE:
            switch (tmp_state) {
            case SINGLE_QUOTE: state = F_SINGLE_STRING_LITERAL; ADVANCE; break;
            case F_NEW_LINE: state = F_FAILED; break; }
            break;
        case DOUBLE_QUOTE:
            switch (tmp_state) {
            case DOUBLE_QUOTE: state = F_DOUBLE_STRING_LITERAL; ADVANCE; break;
            case F_NEW_LINE: state = F_FAILED; break; }
            break;
        case ONE_LINE_COMMENT:
            switch (tmp_state) {
            case F_NEW_LINE: state = F_ONELINE_COMMENT; break; }
            break;
        default:
            printf("Not must be here");
            exit(0);
        }

        if(state > FINISH_STATES) {
            break;
        }
        ADVANCE;
    }

    lexem->type = final_lexem_type[state];

    return lexem;
}
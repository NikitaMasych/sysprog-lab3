#include "../../operator_lexem_parser.h"
#include "../test_helpers.h"

int main() {
    FILE* file = fopen("test_data/operator_lexems", "r");
    initialize_operator_lexem_parser();
    while(1) {
        Lexem* lex = read_operator_lexem(file);
        int expected = read_expected(file);
        if(expected == -1) {
            break;
        }
        expect_equal(expected, lex->type);
    }
}
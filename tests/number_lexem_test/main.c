#include "../../number_lexem_parser.h"
#include "../test_helpers.h"


int main() {
    FILE* file = fopen("test_data/number_lexems", "r");

    while(1) {
        Lexem* lex = read_number_lexem(file);
        int expected = read_expected(file);
        if(expected == -1) {
            break;
        }
        expect_equal(expected, lex->type);
    }
}
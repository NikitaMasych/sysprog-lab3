#include "test_helpers.h"
#include "../helpers.h"

#include <stdio.h>

void expect_equal(LexemType expected, LexemType lexem) {
    if(expected != lexem) {
        printf("expected is %s, lexem is %s\n", from_lexem_type_to_string(expected), from_lexem_type_to_string(lexem));
        exit(0);
    }
}


int read_expected(FILE* file) {
    read_until_white_character(file, NULL);

    char *expected = read_word(file);
    skip_white_character(file);
    if(expected == NULL) {
        return -1;
    }
    return from_string_to_lexem_type(expected);
}
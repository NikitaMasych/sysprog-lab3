#ifndef TEST_HELPERS
#define TEST_HELPERS

#include "../types.h"
#include <stdio.h>
#include <stdlib.h>

void expect_equal(LexemType expected, LexemType lexem);

int read_expected(FILE* file);

#endif
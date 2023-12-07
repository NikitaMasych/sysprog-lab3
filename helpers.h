#ifndef HELPERS
#define HELPERS

#include <stdio.h>


int fpeek(FILE *stream);

int issign(int c);

int add_letter_to_str(char* str, char letter);

int is_white_character(char c);

int skip_white_character(FILE* file);

char* read_word(FILE* file);

void read_until_white_character(FILE* file, char* str);

#endif
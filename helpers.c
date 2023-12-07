#include <stdlib.h>

#include "helpers.h"
#include "types.h"

int fpeek(FILE *stream)
{
    int c;

    c = fgetc(stream);
    ungetc(c, stream);

    return c;
}

int issign(int c) {
    if (c == '+' || c == '-' || c == '/' || c == '*' || c == '.' || c == '>' || c == '<' || c == '=')
    {   
        return 1;
    }

    return 0;
}

int add_letter_to_str(char* str, char letter) {
    int c = 0;
    while(str[c] != '\0') {c++;}
    str[c] = letter;
    str[c + 1] = '\0';
}

int is_white_character(char c) {
    if(c == ' ' || c == '\t') {
        return 1;
    }
    return 0;
}

int skip_white_character(FILE* file) {
    int c = fpeek(file);
    while (is_white_character(c) && c != EOF)
    {
        fgetc(file);
        c = fpeek(file);
    }
}

char* read_word(FILE* file) {
    char* word = malloc(sizeof(char) * MAX_LEXEM_SIZE);
    int pointer = 0;
    skip_white_character(file);
    char c = fpeek(file);
    while (!is_white_character(c) && c != EOF)
    {
        word[pointer] = c;
        pointer++;
        fgetc(file);
        c = fpeek(file);
    }
    if(pointer == 0) {
        free(word);
        return NULL;
    }
    word[pointer] = '\0';
    
    return word;
}

void read_until_white_character(FILE* file, char* str) {
    int c = fgetc(file);
    while (!is_white_character(c) && c != EOF) {
        if(str != NULL)
            add_letter_to_str(str, c);
        c = fgetc(file);
    }
}
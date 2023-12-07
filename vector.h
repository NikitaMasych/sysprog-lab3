#include "types.h"

typedef struct
{
    int real_size;
    int size;
    Lexem **data;
} LexemVector;

void clear_vector(LexemVector *vector);
void add_to_vector(LexemVector* vector, Lexem* element);
LexemVector *create_vector();
void free_vector(LexemVector *vector);
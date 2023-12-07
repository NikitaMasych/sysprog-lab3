#include <stdlib.h>

#include "vector.h"


LexemVector *create_vector()
{
    static const int initial_vector_size = 10;
    LexemVector *tmp_vector = malloc(sizeof(LexemVector));
    tmp_vector->real_size = initial_vector_size;
    tmp_vector->size = 0;
    tmp_vector->data = malloc(sizeof(Lexem*) * initial_vector_size);

    return tmp_vector;
}

void clear_vector(LexemVector *vector) {
    vector->size = 0;
}

void double_vector(LexemVector *vector) {
    const int new_size = vector->real_size*2;
    Lexem **new_data = malloc(sizeof(Lexem*) * new_size);
    for (int i = 0; i < vector->size; i++)
    {
        new_data[i] = vector->data[i];
    }
    
    Lexem **temp = vector->data;
    vector->data = new_data;
    vector->real_size = new_size;
    free(temp);
}

void add_to_vector(LexemVector* vector, Lexem* element) {
    if(vector->size == vector->real_size) {
        double_vector(vector);
    }

    vector->data[vector->size] = element;
    vector->size++;
}

void free_vector(LexemVector *vector) {
    for(int i = 0; i < vector->size; i++) {
        free(vector->data[i]);
    }
    free(vector->data);
    free(vector);
}
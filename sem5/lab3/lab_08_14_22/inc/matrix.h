#ifndef _MATRIX_H_
#include <stdlib.h>

typedef struct
{
    double **data;
    double *head;
    int rows;
    int columns;
    int elements;
} matrix_t;

matrix_t *init_matrix();

double **allocate_matrix(int rows, int columns);

void free_matrix(matrix_t *m);

#define _MATRIX_H_
#endif
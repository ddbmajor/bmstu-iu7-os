#include "matrix.h"


matrix_t *init_matrix()
{
    matrix_t *m = (matrix_t *)malloc(sizeof(matrix_t));
    m->data = NULL;
    m->head = NULL;
    m->rows = 0;
    m->columns = 0;
    m->elements = 0;
    return m;
}


double **allocate_matrix(int rows, int columns)
{
    double **ptrs, *data;
    ptrs = malloc(rows * sizeof(double*));
    if (!ptrs)
        return NULL;
    data = calloc(rows * columns, sizeof(double));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }
    for (int i = 0; i < rows; i++)
        ptrs[i] = data + i * columns;
    return ptrs;
}


void free_matrix(matrix_t *m)
{
    free(m->head);
    free(m->data);
    m->rows = 0;
    m->columns = 0;
    m->elements = 0;
    free(m);
}
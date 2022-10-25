#include "utilities_for_check.h"

int matrix_cmp(matrix_t *m1, matrix_t *m2)
{
    if (m1->rows != m2->rows || m1->columns != m2->columns || m1->elements != m2->elements)
        return -1;
    for (int i = 0; i < m1->rows; i++)
        for (int j = 0; j < m1->columns; j++)
            if (fabs(m1->data[i][j] - m2->data[i][j]) > 1e-8)
                return -2;
    return 0;
}
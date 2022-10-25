#include "iolib.h"


int read_matrix(matrix_t *matrix, FILE *file)
{
    int rc;
    int rows, columns, elements;
    rc = fscanf(file, "%d %d %d", &rows, &columns, &elements);
    if (rc != 3)
    {
        if (feof(file))
            return EMPTY_FILE_ERROR;
        else
            return INPUT_ERROR;
    }
    if (rows <= 0 || columns <= 0 || elements < 0)
        return INPUT_ERROR;
    matrix->data = allocate_matrix(rows, columns);
    if (matrix->data == NULL)
        return MEMORY_ERROR;
    matrix->head = matrix->data[0];
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->elements = elements;

    int row, column;
    double element;
    for (int i = 0; i < elements; i++)
    {
        rc = fscanf(file, "%d %d %lf", &row, &column, &element);
        if (rc != 3)
            return INPUT_ERROR;
        if (row <= 0 || column <= 0)
            return INPUT_ERROR;
        if (row > rows || column > columns)
            return INPUT_ERROR;
        matrix->data[row - 1][column - 1] = element;
    }
    return 0;
}


int print_matrix(FILE *dst, matrix_t *src)
{
    int rc;
    rc = fprintf(dst, "%d %d %d", src->rows, src->columns, src->elements);
    if (rc < 0)
        return PRINT_ERROR;
    for (int i = 0; i < src->rows; i++)
    {
        for (int j = 0; j < src->columns; j++)
        {
            if (fabs(src->data[i][j]) > EPS)
            {
                rc = fprintf(dst, "\n%d %d %lf", i + 1, j + 1, src->data[i][j]);
                if (rc < 0)
                    return PRINT_ERROR;
            }
        }
    }
    return 0;
}
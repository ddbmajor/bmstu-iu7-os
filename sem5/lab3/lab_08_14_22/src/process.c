#include "process.h"


int add(matrix_t *res, matrix_t *m1, matrix_t *m2)
{
    if (m1->rows != m2->rows || m1->columns != m2->columns)
        return DIMENSION_ERROR;
    res->rows = m1->rows;
    res->columns = m1->columns;
    res->data = allocate_matrix(res->rows, res->columns);
    if (res->data == NULL)
        return MEMORY_ERROR;
    res->head = res->data[0];

    int elements = 0;
    double element = 0;
    for (int i = 0; i < res->rows; i++)
    {
        for (int j = 0; j < res->columns; j++)
        {
            element = m1->data[i][j] + m2->data[i][j];
            if (fabs(element) > EPS)
            {
                elements++;
                res->data[i][j] = element;
            }
        }
    }
    res->elements = elements;
    return 0;
}


int mult(matrix_t *res, matrix_t *m1, matrix_t *m2)
{
    if (m1->columns != m2->rows)
        return DIMENSION_ERROR;
    res->rows = m1->rows;
    res->columns = m2->columns;
    res->data = allocate_matrix(res->rows, res->columns);
    if (res->data == NULL)
        return MEMORY_ERROR;
    res->head = res->data[0];

    int elements = 0;
    double sum = 0;
    for (int i = 0; i < res->rows; i++)
    {
        for (int j = 0; j < res->columns; j++)
        {
            sum = 0;
            for (int k = 0; k < m1->columns; k++)
            {
                sum += m1->data[i][k] * m2->data[k][j];
            }
            if (fabs(sum) > EPS)
            {
                res->data[i][j] = sum;
                elements++;
            }
        }
    }
    res->elements = elements;
    return 0;
}


int bin_op(char *result_fn, char *matrix1_fn, char *matrix2_fn, int op(matrix_t*, matrix_t*, matrix_t*))
{
    int rc;

    FILE *m1_f = fopen(matrix1_fn, "r");
    if (m1_f == NULL)
        return OPEN_FILE_ERROR;
    
    matrix_t *matrix1 = init_matrix();
    rc = read_matrix(matrix1, m1_f);
    if (rc != 0)
    {
        free_matrix(matrix1);
        fclose(m1_f);
        return rc;
    }
    fclose(m1_f);

    FILE *m2_f = fopen(matrix2_fn, "r");
    if (m2_f == NULL)
    {
        free_matrix(matrix1);
        return OPEN_FILE_ERROR;
    }
    matrix_t *matrix2 = init_matrix();
    rc = read_matrix(matrix2, m2_f);
    if (rc != 0)
    {
        free_matrix(matrix1);
        free_matrix(matrix2);
        fclose(m2_f);
        return rc;
    }
    fclose(m2_f);

    matrix_t *result = init_matrix();
    rc = op(result, matrix1, matrix2);
    if (rc != 0)
    {
        free_matrix(matrix1);
        free_matrix(matrix2);
        free_matrix(result);
        return rc;
    }
    free_matrix(matrix1);
    free_matrix(matrix2);

    FILE *res_f = fopen(result_fn, "w");
    if (res_f == NULL)
    {
        free_matrix(result);
        return OPEN_FILE_ERROR;
    }
    rc = print_matrix(res_f, result);
    if (rc != 0)
    {
        fclose(res_f);
        free_matrix(result);
        return rc;
    }
    fclose(res_f);
    free_matrix(result);
    return 0;
}


void get_help_matrix(matrix_t *res, matrix_t *m, int row)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            res->data[i][j] = m->data[i][j];
        }
    }
    for (int i = 0; i < m->rows; i++)
        res->data[i][res->columns - 1] = 0;
    res->data[row][res->columns - 1] = 1;
}


void swap_rows(matrix_t *m, int i, int j)
{
    double *tmp;
    tmp = m->data[i];
    m->data[i] = m->data[j];
    m->data[j] = tmp;
}


int invert_op(matrix_t *res, matrix_t *m)
{
    if (m->columns != m->rows)
        return DIMENSION_ERROR;
    
    res->data = allocate_matrix(m->rows, m->columns);
    res->head = res->data[0];
    res->rows = m->rows;
    res->columns = m->columns;
    res->elements = 0;

    matrix_t *tmp_m = init_matrix();
    tmp_m->data = allocate_matrix(m->rows, m->columns + 1);
    tmp_m->head = tmp_m->data[0];
    tmp_m->rows = m->rows;
    tmp_m->columns = m->columns + 1;

    for (int i = 0; i < res->columns; i++)
    {
        // подставляем новый столбец единичной матрицы
        get_help_matrix(tmp_m, m, i);
        // приводим к ступенчатому виду
        for (int j = 0; j < tmp_m->columns - 1; j++)
        {
            // ищем первый ненулевой эл-т в j-ом стоблце после j-1-ой строки
            int flag = 0;
            for (int k = j; k < tmp_m->rows; k++)
            {
                if (fabs(tmp_m->data[k][j]) > EPS)
                {
                    flag = 1;
                    swap_rows(tmp_m, k, j);
                    break;
                }
            }
            if (flag == 0)
            {
                free_matrix(tmp_m);
                return DET_ERROR;
            }
            // делим j-ую строку на [j][j] элемент
            double del = tmp_m->data[j][j];
            for (int k = 0; k < tmp_m->columns; k++)
            {
                tmp_m->data[j][k] /= del;   
            }
            // вычитаем из всех последующих строк j-ю строку, умноженную на [k][j] элемент;
            for (int k = j + 1; k < tmp_m->rows; k++)
            {
                double mnoj = tmp_m->data[k][j];
                for (int q = 0; q < tmp_m->columns; q++)
                {
                    tmp_m->data[k][q] -= tmp_m->data[j][q] * mnoj;
                }
            }
        }
        // получили ступенчатый вид
        // обратный ход
        for (int j = tmp_m->rows - 1; j >= 0; j--)
        {
            for (int k = j - 1; k >= 0; k--)
            {
                double mnoj = tmp_m->data[k][j];
                for (int q = 0; q < tmp_m->columns; q++)
                {
                    tmp_m->data[k][q] -= tmp_m->data[j][q] * mnoj;
                }
            }
        }
        // теперь у нас есть последний столбец, являющимся i-ым стоблцом в исходной обратной матрице
        // записываем его в результат
        for (int j = 0; j < tmp_m->rows; j++)
            res->data[j][i] = tmp_m->data[j][tmp_m->columns - 1];
    }
    free_matrix(tmp_m);
    for (int i = 0; i < res->rows; i++)
        for (int j = 0; j < res->columns; j++)
            if (fabs(res->data[i][j]) > EPS)
                (res->elements)++;
    return 0;
}


int invert(char *result_fn, char *matrix_fn)
{
    int rc;

    FILE *m_f = fopen(matrix_fn, "r");
    if (m_f == NULL)
        return OPEN_FILE_ERROR;
    
    matrix_t *matrix = init_matrix();
    rc = read_matrix(matrix, m_f);
    if (rc != 0)
    {
        free_matrix(matrix);
        fclose(m_f);
        return rc;
    }
    fclose(m_f);

    matrix_t *result = init_matrix();
    rc = invert_op(result, matrix);
    if (rc != 0)
    {
        free_matrix(result);
        free_matrix(matrix);
        return rc;
    }
    free_matrix(matrix);

    FILE *res_f = fopen(result_fn, "w");
    if (res_f == NULL)
    {
        free_matrix(result);
        return OPEN_FILE_ERROR;
    }
    rc = print_matrix(res_f, result);
    if (rc != 0)
    {
        fclose(res_f);
        free_matrix(result);
        return rc;
    }
    fclose(res_f);
    free_matrix(result);
    return 0;
}
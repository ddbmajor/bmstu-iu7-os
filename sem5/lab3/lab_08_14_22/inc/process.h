#ifndef _PROCESS_H_
#include <stdio.h>
#include <math.h>
#include "defines.h"
#include "matrix.h"
#include "iolib.h"

int add(matrix_t *res, matrix_t *m1, matrix_t *m2);

int mult(matrix_t *res, matrix_t *m1, matrix_t *m2);

int bin_op(char *result_fn, char *matrix1_fn, char *matrix2_fn, int op(matrix_t*, matrix_t*, matrix_t*));

void get_help_matrix(matrix_t *res, matrix_t *m, int row);

void swap_rows(matrix_t *m, int i, int j);

int invert_op(matrix_t *res, matrix_t *m);

int invert(char *result_fn, char *matrix_fn);

#define _PROCESS_H_
#endif
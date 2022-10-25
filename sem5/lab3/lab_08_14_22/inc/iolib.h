#ifndef _IOLIB_H_
#include <stdio.h>
#include <math.h>
#include "defines.h"
#include "matrix.h"

int read_matrix(matrix_t *matrix, FILE *file);

int print_matrix(FILE *dst, matrix_t *src);

#define _IOLIB_H_
#endif
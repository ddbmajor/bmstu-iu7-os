#ifndef _IOLIB_H_
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"


int getcount(FILE *f, int *count);

void getarray(int *arr, int count, FILE *f);

int arrtofile(FILE *f, int *arr, int *arr_end);
#endif
#define _IOLIB_H_
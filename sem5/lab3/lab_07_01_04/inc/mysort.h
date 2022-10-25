#ifndef _MYSORT_H_
#include <stdlib.h>
#include <math.h>
#include <string.h>

int compare_string(const void *left, const void *right);

int compare_float(const void *left, const void *right);

int compare_int(const void *left, const void *right);

void push(void *first, void *second, size_t size);

void mysort(void *base, int num, size_t size, int (*compare)(const void *, const void *));
#endif
#define _MYSORT_H_
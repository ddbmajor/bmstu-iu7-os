#include "../inc/mysort.h"


int compare_string(const void *left, const void *right)
{
    const char *l = left;
    const char *r = right;
    return strcmp(l, r); 
}


int compare_float(const void *left, const void *right)
{
    const float *l = left;
    const float *r = right;
    if (fabs(*l - *r) < 1e-8)
        return 0;
    else if (*l < *r)
        return -1;
    else
        return 1;
}


int compare_int(const void *left, const void *right)
{
    const int *l = left;
    const int *r = right;
    return *l - *r;
}


void push(void *first, void *second, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        *((char *) first + i) = *((char *) second + i);
}


void mysort(void *base, int num, size_t size, int (*compare)(const void *, const void *))
{
    if (num == 1)
        return;
    char *start = (char *)base;
    char *key = malloc(size);
    if (key == NULL)
    {
        free(key);
        return;
    }

    int j;
    for (int i = 1; i < num; i++)
    {
        push(key, start + i * size, size);
        j = i - 1;
        while (j >= 0 && compare(key, start + j * size) < 0)
        {
            push(start + (j + 1) * size, start + j * size, size);
            j--;
        }
        push(start + (j + 1) * size, key, size);
    }
    free(key);
}
#include "../inc/key.h"


int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL)
        return BAD_ARRAY_ERROR;

    if (pb_src == pe_src)
        return EMPTY_FILE_ERROR;

    const int *curr = pb_src;
    float average = 0;
    int count = 0;

    while (curr < pe_src)
    {
        average += *curr;
        count++;
        curr++;
    }
    average /= count;

    curr = pb_src;
    count = 0;

    while (curr < pe_src)
    {
        if (*curr > average)
            count++;
        curr++;
    }
    if (count == 0)
        return EMPTY_FILE_ERROR;

    *pb_dst = (int *)malloc(count * sizeof(int));
    if (*pb_dst == NULL)
    {
        free(*pb_dst);
        return ALLOC_ERROR;
    }
    *pe_dst = *pb_dst;

    curr = pb_src;
    while (curr < pe_src)
    {
        if (*curr > average)
        {
            **pe_dst = *curr;
            (*pe_dst)++;
        }
        curr++;
    }

    return 0;
}
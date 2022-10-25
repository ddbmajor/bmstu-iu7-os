#include "../inc/iolib.h"

int getcount(FILE *f, int *count)
{
    int counter = 0;
    int tmp;

    while (!feof(f))
    {
        if (fscanf(f, "%d", &tmp) == 1)
            counter++;
        else
            break;
    }
    if (counter == 0 && feof(f))
        return EMPTY_FILE_ERROR;
    else if (counter != 0 && !feof(f))
        return INPUT_ERROR;
    else
        *count = counter;
    return 0;
}


void getarray(int *arr, int count, FILE *f)
{
    for (int i = 0; i < count; i++)
        fscanf(f, "%d", arr + i);
}


int arrtofile(FILE *f, int *arr, int *arr_end)
{
    int rc;

    if (arr == arr_end)
        return EMPTY_FILE_ERROR;
    
    int *curr = arr;
    while (curr < arr_end)
    {
        rc = fprintf(f, "%d ", *curr);
        if (rc < 0)
            return PRINT_ERROR;
        curr++;
    }
    return 0;
}
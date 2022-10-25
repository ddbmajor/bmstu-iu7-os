#include "../inc/process.h"


int filtsortfile(char *infilename, char *outfilename)
{
    FILE *infile = fopen(infilename, "r");
    if (infile == NULL)
        return OPEN_FILE_ERROR;
    
    int rc;
    int count;
    rc = getcount(infile, &count);
    if (rc != 0)
    {
        fclose(infile);
        return rc;
    }
    rewind(infile);

    int *data = (int *)malloc(count * sizeof(int));
    if (data == NULL)
    {
        fclose(infile);
        free(data);
        return ALLOC_ERROR;
    }
    
    getarray(data, count, infile);
    fclose(infile);

    int *filtered_data = NULL;
    int *filtered_data_end = NULL;

    rc = key(data, data + count, &filtered_data, &filtered_data_end);
    free(data);
    if (rc != 0)
        return rc;

    mysort(filtered_data, filtered_data_end - filtered_data, sizeof(int), compare_int);

    FILE *outfile = fopen(outfilename, "w");
    if (outfile == NULL)
    {
        free(filtered_data);
        return OPEN_FILE_ERROR;
    }
    
    rc = arrtofile(outfile, filtered_data, filtered_data_end);
    free(filtered_data);
    fclose(outfile);
    if (rc != 0)
        return rc;

    return 0;
}


int sortfile(char *infilename, char *outfilename)
{
    FILE *infile = fopen(infilename, "r");
    if (infile == NULL)
        return OPEN_FILE_ERROR;
    
    int rc;
    int count;
    rc = getcount(infile, &count);
    if (rc != 0)
    {
        fclose(infile);
        return rc;
    }
    rewind(infile);

    int *data = (int *)malloc(count * sizeof(int));
    if (data == NULL)
    {
        fclose(infile);
        free(data);
        return ALLOC_ERROR;
    }
    
    getarray(data, count, infile);
    fclose(infile);

    mysort(data, count, sizeof(int), compare_int);

    FILE *outfile = fopen(outfilename, "w");
    if (outfile == NULL)
    {
        free(data);
        return OPEN_FILE_ERROR;
    }
    
    rc = arrtofile(outfile, data, data + count);
    free(data);
    fclose(outfile);
    if (rc != 0)
        return rc;
        
    return 0;
}
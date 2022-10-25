#include <string.h>
#include "defines.h"
#include "process.h"


int main(int argc, char **argv)
{
    int rc;
    // check args
    if (argc < 4)
        return ARG_ERROR;
    if (strcmp(argv[1], "a") == 0)
    {
        if (argc == 5)
        {
            rc = bin_op(argv[4], argv[2], argv[3], add);
            if (rc != 0)
                return rc;
        }
        else
            return ARG_ERROR;
    }
    else if (strcmp(argv[1], "m") == 0)
    {
        if (argc == 5)
        {
            rc = bin_op(argv[4], argv[2], argv[3], mult);
            if (rc != 0)
                return rc;
        }
        else
            return ARG_ERROR;
    }
    else if (strcmp(argv[1], "o") == 0)
    {
        if (argc == 4)
        {
            rc = invert(argv[3], argv[2]);
            if (rc != 0)
                return rc;
        }
        else
            return ARG_ERROR;
    }
    else
        return ARG_ERROR;
    return 0;
}
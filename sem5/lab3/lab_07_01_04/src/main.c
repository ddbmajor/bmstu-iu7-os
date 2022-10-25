#include <string.h>
#include "../inc/process.h"
#include "../inc/defines.h"


int main(int argc, char **argv)
{
    if (argc == 3)
    {
        int rc;
        rc = sortfile(argv[1], argv[2]);
        if (rc != 0)
            return rc;
    }
    else if (argc == 4 && strcmp(argv[3], "f") == 0)
    {
        int rc;
        rc = filtsortfile(argv[1], argv[2]);
        if (rc != 0)
            return rc;
    }
    else
        return ARG_ERROR;
}
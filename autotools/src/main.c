#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif
#include "function.h"
#include "myconfig.h"

int main(int argc, char *argv[])
{
    #ifdef _DEV_
        printf("------------ CONFIGURATION ------------\n");
        printf("- config: %s\n", CFG_NAME);
        printf("- tryb developera\n");
        printf("---------------------------------------\n");
    #endif

    if(argc<3)
    {
        printf("Za malo argumentow\n");
    }
    else
    {
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        printf("SUMA: %d+%d=%d\n", a, b, sum(a, b));
        printf("RÓŻNICA: %d-%d=%d\n", a, b, subtract(a, b));
    }

    return 0;
}
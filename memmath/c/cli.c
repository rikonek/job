#include <stdio.h>
#include <stdlib.h>
#include "memmath.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage:\n");
        printf("  %s arg1 arg2 [...]\n", argv[0]);
        return 0;
    }

    struct ListElement *head = NULL;
    for (int i = 1; i < argc; i++)
    {
        addNumber(&head, argv[i]);
    }

    int loop = true;
    while (loop)
    {
        if (!sum(&head))
        {
            loop = false;
        }
    }

    free(head);

    return 0;
}
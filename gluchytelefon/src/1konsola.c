#include "gluchytelefon.h"
#include "1konsola.h"

// 1. "Konsola":
// wejście: stdin
// Modyfikacja/wyjscie: x:=x+1

int main()
{
    signal(SIGINT, breakHandler);

    long int number=0;
    while(1)
    {
        printf("\n\n\n");
        displayInfo(INTRO, "#####     1     #####   x=x+1");

        printf("Enter number [0-%u]: ", UINT_MAX);
        if(scanf("%ld", &number))
        {
            char buffer[BUFFER_SIZE];
            if(!checkRange(number))
            {
                displayInfo(ERROR, TXT_ERROR_INPUT_OUT_OF_RANGE);
                continue;
            }
            sprintf(buffer, "%ld", number);
            displayInfo(INPUT, buffer);

            number=transform(number);
            if(!checkRange(number))
            {
                displayInfo(ERROR, TXT_ERROR_OUTPUT_OUT_OF_RANGE);
                continue;
            }
            sprintf(buffer, "%ld", number);
            displayInfo(OUTPUT, buffer);

            send((unsigned int) number);
        }
        else
        {
            scanf("%*s");
            displayInfo(ERROR, "Incorrect characters");
        }
    }
    return 0;
}

void breakHandler()
{
    printf("\nShutting down...\n");
    exit(0);
}

void send(const unsigned int number)
{
    char *pTxt=NULL;
    asprintf(&pTxt, "./2argument.out -i %u", number);
    system(pTxt);
    free(pTxt);
}

long int transform(long int number)
{
    return ++number;
}
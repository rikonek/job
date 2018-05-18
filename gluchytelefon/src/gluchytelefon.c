#include "gluchytelefon.h"

bool checkRange(const long int number)
{
    if(number<0 || number>UINT_MAX)
    {
        return false;
    }
    return true;
}

void displayBits(unsigned int number)
{
    unsigned int size=sizeof(number)*8;
    unsigned mask = 1 << (size-1);

    printf("%10u = ", number);

    for(unsigned int i=1; i<=size; i++)
    {
        putchar(number & mask ? '1' : '0');
        number <<= 1;
        if(i%8==0)
        {
            putchar(' ');
        }
    }
    putchar('\n');
}

void displayInfo(infoType type, char txt[])
{
    switch(type)
    {
        case ERROR:
            printf("["CMD_RED"ERROR"CMD_RESET"] %s\n", txt);
            break;

        case INPUT:
            printf("["CMD_YELLOW"INPUT"CMD_RESET"]  %s\n", txt);
            break;

        case INTRO:
            printf(CMD_BG_VIOLET"%s"CMD_RESET"\n", txt);
            break;

        case OK:
            printf("["CMD_GREEN"OK"CMD_RESET"] %s\n", txt);
            break;

        case OUTPUT:
            printf("["CMD_ORANGE"OUTPUT"CMD_RESET"] %s\n", txt);
            break;
    }
}
#include "gluchytelefon.h"
#include "5netlink.h"

// 5. "Netlink"
// Wejście: Generic netlink
// Modyfikacja/wyjscie: jeżeli liczba jest parzysta -> x=x/2, jeżeli nie -> przeksztalcenie bitowe według schematu ABCD -> BDAC, gdzie A,B,C i D to 8bitowe czastki liczby wejsciowej

int main()
{
    displayInfo(INTRO, "#####     5     #####   even -> x=x/2, odd -> octet reverse (ABCD->BDAC)");

    char buffer[BUFFER_SIZE];

    // long int number=receive();
    long int number=2151686159;

    sprintf(buffer, "%ld", number);
    displayInfo(INPUT, buffer);
    if(!checkRange(number))
    {
        displayInfo(ERROR, TXT_ERROR_INPUT_OUT_OF_RANGE);
        return 0;
    }

    unsigned int reverse=transform((unsigned int) number);
    if(!checkRange(reverse))
    {
        displayInfo(ERROR, TXT_ERROR_OUTPUT_OUT_OF_RANGE);
        return 0;
    }
    sprintf(buffer, "%u", reverse);
    displayInfo(OUTPUT, buffer);

    // send(reverse);
    return 0;
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

unsigned int transform(unsigned int number) // 32 bit reverse
{
    // ABCD -> BDAC

    if(number%2==0) // odd
    {
        return (number/2);
    }
    else // even
    {
        displayBits(number);

        // unsigned int offset=0;
        // unsigned int octet=0;

        unsigned int size=sizeof(number)*8;
        unsigned mask = 1 << (size-1);
        unsigned int reverse=0;

        for(unsigned int i=1; i<=size; i++)
        {
            // switch(octet)
            // {
            //     case 0: offset=2; break;
            //     case 1: offset=0; break;
            //     case 2: offset=3; break;
            //     case 3: offset=1; break;
            // }
            putchar(number & mask ? '1' : '0');
            printf(":%i\n", size-i);
            reverse |= (number & mask) << (size-i);
            number <<= 1;
            // displayBits(reverse);
        }
        printf("\n");

        printf("End:\n");
        displayBits(reverse);

        // reverse |= (number & 1) << (size-i);
        // number >>= 1;

        return reverse;

    }
}
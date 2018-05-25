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
    long int number = 2151686159;
    if (!checkRange(number))
    {
        displayInfo(ERROR, TXT_ERROR_INPUT_OUT_OF_RANGE);
        return 0;
    }
    sprintf(buffer, "%ld", number);
    displayInfo(INPUT, buffer);
    if (number % 2 == 1)
    {
        displayBits(number);
    }

    unsigned int reverse = transform((unsigned int)number);
    if (number % 2 == 1)
    {
        displayBits(reverse);
    }
    sprintf(buffer, "%u", reverse);
    displayInfo(OUTPUT, buffer);

    // send(reverse);
    return 0;
}

unsigned int transform(unsigned int number) // 32 bit reverse
{
    if (number % 2 == 0) // odd
    {
        return (number / 2);
    }
    else // even
    {
        unsigned int octet = 0;
        unsigned int shift = 0;
        unsigned int position = 0;

        unsigned int size = sizeof(number) * 8;
        unsigned int mask = 1 << (size - 1);
        unsigned int reverse = 0;

        for (unsigned int i = 1; i <= size; i++)
        {
            switch (octet)
            {
            case 0:
                shift = 2;
                break;
            case 1:
                shift = 0;
                break;
            case 2:
                shift = 3;
                break;
            case 3:
                shift = 1;
                break;
            }
            reverse |= (number & mask) >> (position + (shift * 8));
            number <<= 1;
            if (i % 8 == 0)
            {
                octet++;
            }
            position++;
            if (position % 8 == 0)
            {
                position = 0;
            }
        }

        return reverse;
    }
}
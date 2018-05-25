#include "gluchytelefon.h"
#include "4jajko.h"

// 4. "Jajko"
// Wejście: interfejs znakowy (linux kernel module over chrdev)
// Modyfikacja/wyjscie: Liczba ciagu Fibonacciego odpowiadajaca otrzymanemu numerowi

int main()
{
    displayInfo(INTRO, "#####     4     #####   Fibonacci number");
    char buffer[BUFFER_SIZE];

    long int number = receive();
    sprintf(buffer, "%ld", number);
    displayInfo(INPUT, buffer);
    if (!checkRange(number))
    {
        displayInfo(ERROR, TXT_ERROR_INPUT_OUT_OF_RANGE);
        return 0;
    }

    number = transform(number);
    if (!checkRange(number))
    {
        displayInfo(ERROR, TXT_ERROR_OUTPUT_OUT_OF_RANGE);
        return 0;
    }
    sprintf(buffer, "%ld", number);
    displayInfo(OUTPUT, buffer);

    send(number);
    return 0;
}

long int receive()
{
    int fd;
    char buffer[sizeof(int) * 8];
    fd = open(CHRDEV_PATH, O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open the device CHRDEV");
        exit(0);
    }
    if (read(fd, buffer, sizeof(int) * 8) < 0)
    {
        perror("Couldn't read from CHRDEV");
        exit(0);
    }
    close(fd);

    return atol(buffer);
}

void send(const unsigned int number)
{
    // In progress...
}

long int transform(const long int number)
{
    if (number < 0)
    {
        return -1;
    }
    if (number == 0 || number == 1)
    {
        return number;
    }
    long int prev = 0, current = 1, helper = 0;
    for (unsigned int i = 2; i <= number; i++)
    {
        helper = prev + current;
        prev = current;
        current = helper;
        if (!checkRange(current))
        {
            return -1;
        }
    }
    return current;
}
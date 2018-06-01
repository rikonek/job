#include "gluchytelefon.h"
#include "4jajko.h"
#include "genl.h"

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

    gt_send(number);
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

void gt_send(const unsigned int number)
{
    pid_t pid;
    if ((pid = fork()) == -1)
    {
        perror("Fork error");
        exit(0);
    }
    else
    {
        if (pid == 0)
        {
            usleep(10000); // waiting for next step process
            struct nl_sock *nlsock = NULL;
            gt_genl_prep_sock(&nlsock);

            char *message = NULL;
            asprintf(&message, "%u", number);
            gt_genl_send_msg(nlsock, message);
            free(message);
            exit(0);
        }
    }

    execl("./5netlink.out", "software", NULL);
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
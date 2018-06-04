#include "gluchytelefon.h"
#include "5netlink.h"
#include "genl.h"

// 5. "Netlink"
// Wejście: Generic netlink
// Modyfikacja/wyjscie: jeżeli liczba jest parzysta -> x=x/2, jeżeli nie -> przeksztalcenie bitowe według schematu ABCD -> BDAC, gdzie A,B,C i D to 8bitowe czastki liczby wejsciowej

int main()
{
    displayInfo(INTRO, "#####     5     #####   even -> x=x/2, odd -> octet reverse (ABCD->BDAC)");
    char buffer[BUFFER_SIZE];

    long int number = receive();
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

    gt_send(reverse);
    return 0;
}

void inetServer(const unsigned int number)
{
    int server_fd, client_fd;
    int backlog = 5;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(TCP_PORT); // network byte order

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("socket");
        exit(0);
    }

    int yes = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes, sizeof(yes)))
    {
        perror("setsockopt");
        exit(0);
    }
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(0);
    }
    if (listen(server_fd, backlog) < 0)
    {
        perror("listen");
        exit(0);
    }

    socklen_t client_addr_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0)
    {
        perror("accept");
        exit(0);
    }

    sprintf(buffer, "%u", number);
    if (write(client_fd, buffer, sizeof(buffer)) < 0)
    {
        perror("write");
        exit(0);
    }

    close(client_fd);
    close(server_fd);
}

long int receive()
{
    struct nl_sock *nlsock = NULL;
    struct nl_cb *nlcb = NULL; // callback

    gt_add_group(GT_GENL_MCGRP0);

    gt_genl_prep_sock(&nlsock);

    nlcb = nl_cb_alloc(NL_CB_DEFAULT);
    nl_cb_set(nlcb, NL_CB_SEQ_CHECK, NL_CB_CUSTOM, gt_skip_seq_check, NULL);
    nl_cb_set(nlcb, NL_CB_VALID, NL_CB_CUSTOM, gt_genl_receive_msg, NULL);

    nl_recvmsgs(nlsock, nlcb);
    nl_cb_put(nlcb);

    return atol(gt_get_message());
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
            inetServer(number);
            exit(0);
        }
    }

    execl("./6siec.out", "software", NULL);
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
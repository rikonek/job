#include "gluchytelefon.h"
#include "6siec.h"

// 6. "Sieć"
// Wejście: Stream tcp
// Wyjście: stdout na osobnej konsoli -> zmodyfikowana liczba lub info o przekroczeniu zakresu

int main()
{
    displayInfo(INTRO, "#####     6     ##### output on new console");
    long int number = receive();
    gt_send(number);
    return 0;
}

long int receive()
{
    int client_fd;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE] = {0};

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        perror("socket");
        exit(0);
    }
    server = gethostbyname(TCP_HOST);
    if (server == NULL)
    {
        perror("gethostbyname");
        exit(0);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TCP_PORT); // network byte order
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        exit(0);
    }

    if (read(client_fd, buffer, sizeof(buffer)) < 0)
    {
        perror("read");
        exit(0);
    }

    close(client_fd);

    return atol(buffer);
}

void gt_send(const long int number)
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
            char *pTxt = NULL;
            if (checkRange(number))
            {
                asprintf(&pTxt, "%ld", number);
            }
            else
            {
                asprintf(&pTxt, "%s", TXT_ERROR_OUTPUT_OUT_OF_RANGE);
            }
            execl("/usr/bin/xterm", "xterm", "-hold", "-e", "echo", pTxt, NULL);
            free(pTxt);
        }
    }
}
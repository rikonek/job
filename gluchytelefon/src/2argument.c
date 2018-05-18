#include "gluchytelefon.h"
#include "2argument.h"

// 2. "Argument"
// Wejście: argument do programu, parsowana za pomocą getopt
// Modyfikacja/wyjscie: x:= lustrzane odbicie bitów, np dla 6(110):= 3(011)

int main(int argc, char *argv[])
{
    displayInfo(INTRO, "#####     2     #####   bit reverse");
    char buffer[BUFFER_SIZE];

    long int number=parseCmdOption(argc, argv);
    if(!checkRange(number))
    {
        displayInfo(ERROR, TXT_ERROR_INPUT_OUT_OF_RANGE);
        return 0;
    }
    sprintf(buffer, "%ld", number);
    displayInfo(INPUT, buffer);
    displayBits(number);

    unsigned int reverse=transform((unsigned int) number);
    displayBits(reverse);
    sprintf(buffer, "%u", reverse);
    displayInfo(OUTPUT, buffer);

    send(reverse);
    return 0;
}

long int parseCmdOption(int argc, char *argv[])
{
    int param;
    long int number=0;
    while((param = getopt(argc, argv, "hi:")) != -1)
    {
        switch(param)
        {
            case 'i': // input
                number=atol(optarg);
                return number;
                break;

            case 'h': // help
            default:
                printf("Usage:\n\t%s -i [0-%u]\n", argv[0], UINT_MAX);
                exit(0);
                break;
        }
    }
    return -1;
}

void send(const unsigned int number)
{
	int fd;
    unlink(FIFO_PATH);
	mkfifo(FIFO_PATH,0666);

    pid_t pid;
    if( (pid=fork()) == -1)
    {
        perror("Fork error");
        exit(0);
    }
    else
    {
        if(pid==0)
        {
            char *pTxt=NULL;
            asprintf(&pTxt, "%u", number);
            fd=open(FIFO_PATH,O_WRONLY);
            if( write(fd,pTxt,sizeof(int)*8) < 0 )
            {
                perror("Couldn't write to FIFO");
                exit(0);
            }
            close(fd);
            free(pTxt);
            exit(0);
        }
    }

    execl("./3pipe.out", "software", NULL);
}

unsigned int transform(unsigned int number) // 32 bit reverse
{
    unsigned int size=sizeof(number)*8;
    unsigned int reverse=0;

    for(unsigned int i=1; i<=size; i++)
    {
        reverse |= (number & 1) << (size-i);
        number >>= 1;
    }

    return reverse;
}
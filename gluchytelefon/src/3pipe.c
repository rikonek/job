#include "gluchytelefon.h"
#include "3pipe.h"

// 3. "Pipe"
// Wejście: Nazwany pipe
// Modyfikacja/wyjscie: Nastepna liczba pierwsza

int main()
{
    displayInfo(INTRO, "#####     3     #####   next prime number");
    char buffer[BUFFER_SIZE];

    long int number=receive();
    sprintf(buffer, "%ld", number);
    displayInfo(INPUT, buffer);
    if(!checkRange(number))
    {
        displayInfo(ERROR, TXT_ERROR_INPUT_OUT_OF_RANGE);
        return 0;
    }

    number=transform(number);
    if(!checkRange(number))
    {
        displayInfo(ERROR, TXT_ERROR_OUTPUT_OUT_OF_RANGE);
        return 0;
    }
    sprintf(buffer, "%ld", number);
    displayInfo(OUTPUT, buffer);

    send(number);
    return 0;
}

bool isPrime(const unsigned long number) //trialDivision
{
    if(number<=1) return false;
    if(number==2) return true;
    for(unsigned int i=2; (i*i)<=number; ++i)
    {
        if(number%i==0) return false;
    }
    return true;
}

long int receive()
{
	int fd;
    char buffer[sizeof(int)*8];
	fd=open(FIFO_PATH,O_RDONLY);
    if( read(fd,buffer,sizeof(int)*8) < 0 )
    {
        perror("Couldn't read from FIFO");
        exit(0);
    }
	close(fd);
    unlink(FIFO_PATH);

    return atol(buffer);
}

void send(const unsigned int number)
{
    int fd;

    char *pTxt=NULL;
    asprintf(&pTxt, "%u", number);
    fd=open(CHRDEV_PATH,O_WRONLY);
    if(fd<0)
    {
        perror("Failed to open the device CHRDEV");
        exit(0);
    }
    if( write(fd,pTxt,sizeof(int)*8) < 0 )
    {
        perror("Couldn't write to CHRDEV");
        exit(0);
    }
    close(fd);
    free(pTxt);

    execl("./4jajko.out", "software", NULL);
}

long int transform(long int number)
{
    bool prime=false;
    while(!prime)
    {
        number++;
        if(!checkRange(number)) return -1;
        if(isPrime(number)) prime=true;
    }
    return number;
}
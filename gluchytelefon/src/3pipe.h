#ifndef _3PIPE_H_
#define _3PIPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

bool isPrime(const unsigned long);
long int receive();
void send(const unsigned int);
long int transform(long int);

#endif
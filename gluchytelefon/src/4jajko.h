#ifndef _4JAJKO_H_
#define _4JAJKO_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

long int receive();
void send(const unsigned int);
long int transform(const long int);

#endif
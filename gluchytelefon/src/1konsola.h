#ifndef _1KONSOLA_H_
#define _1KONSOLA_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>

void breakHandler();
void send(const unsigned int);
long int transform(long int);

#endif
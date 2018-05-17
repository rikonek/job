#ifndef _2ARGUMENT_H_
#define _2ARGUMENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

void displayBits(unsigned int);
long int parseCmdOption(int, char *[]);
void send(const unsigned int);
unsigned int transform(unsigned int);

#endif
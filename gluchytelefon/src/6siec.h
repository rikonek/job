#ifndef _6SIEC_H_
#define _6SIEC_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

long int receive();
void gt_send(const long int);

#endif
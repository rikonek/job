#ifndef _5NETLINK_H_
#define _5NETLINK_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void inetServer(const unsigned int);
long int receive();
void gt_send(const unsigned int);
unsigned int transform(unsigned int);

#endif
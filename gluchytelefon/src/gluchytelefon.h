#ifndef _GLUCHYTELEFON_H_
#define _GLUCHYTELEFON_H_

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define BUFFER_SIZE 255
#define FIFO_PATH "/tmp/gluchytelefon"
#define CHRDEV_PATH "/dev/jajko"

#define CMD_RESET "\x1b[0m"
#define CMD_RED "\x1b[31m"
#define CMD_GREEN "\x1b[32m"
#define CMD_ORANGE "\x1b[33m"
#define CMD_YELLOW "\x1b[38;5;11m"
#define CMD_BG_VIOLET "\x1b[48;5;57m"

#define TXT_ERROR_INPUT_OUT_OF_RANGE "Input is out of range"
#define TXT_ERROR_OUTPUT_OUT_OF_RANGE "Output is out of range"

typedef enum infoType { ERROR, INPUT, INTRO, OK, OUTPUT } infoType;

bool checkRange(const long int);
void displayBits(unsigned int);
void displayInfo(infoType, char []);

#endif
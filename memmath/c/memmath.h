#include <stdbool.h>

#ifndef _MEMMATH_H
#define _MEMMATH_H

#define MAX_LENGTH 14
#define MAX_LENGTH_AVAIL 13

struct ListElement
{
    char number[MAX_LENGTH]; // int32, range negative 2,147,483,648 to positive 2,147,483,647
    struct ListElement *next;
};

struct MemStruct
{
    char a[MAX_LENGTH];
    char b[MAX_LENGTH];
    char result[MAX_LENGTH];
    char helper[MAX_LENGTH];
};

void addNumber(struct ListElement **head, char *number);
bool sum(struct ListElement **head);

#endif
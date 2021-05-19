#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memmath.h"

#define SIGN_SPACE 2

void resizeString(char *src, char *dst, int dstlen)
{
    char format[MAX_LENGTH];
    sprintf(format, "%%%ds", dstlen);
    sprintf(dst, format, src);
}

void pushFrontNumber(struct ListElement **head, char *number)
{
    struct ListElement *current = malloc(sizeof(struct ListElement));
    if (!current)
        perror("Malloc error");

    strcpy(current->number, number);
    current->next = *head;
    *head = current;
}

void pushBackNumber(struct ListElement **head, char *number)
{
    struct ListElement *new = malloc(sizeof(struct ListElement));
    if (!new)
        perror("Malloc error");

    strcpy(new->number, number);
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        struct ListElement *current = *head;

        while (current->next != NULL)
            current = current->next;

        current->next = new;
    }
}

void popNumber(struct ListElement **head, char *number)
{
    if (*head != NULL)
    {
        strcpy(number, (*head)->number);

        struct ListElement *tmp = NULL;

        if (*head != NULL)
        {
            tmp = (*head)->next;
            free(*head);
            *head = tmp;
        }
    }
}

void addNumber(struct ListElement **head, char *number)
{
    int len;
    len = strlen(number) + 1;
    char num[len];
    sprintf(num, "%i", atoi(number));
    pushBackNumber(head, num);
}

void operSum(struct MemStruct *s)
{
    int max_len_number = strlen(s->a);
    int sum;
    char number[2];
    char sum_str[max_len_number];

    resizeString("", s->result, max_len_number);
    resizeString("", s->helper, max_len_number);

    for (int i = (max_len_number - 1); i >= (SIGN_SPACE + 1); i--)
    {
        sum = 0;

        sprintf(number, "%c", s->a[i]);
        sum += atoi(number);

        sprintf(number, "%c", s->b[i]);
        sum += atoi(number);

        sprintf(number, "%c", s->helper[i]);
        sum += atoi(number);

        sprintf(sum_str, "%d", sum);
        if (strlen(sum_str) == 2)
        {
            s->helper[i - 1] = sum_str[0];
            s->result[i] = sum_str[1];
        }
        else
        {
            s->helper[i - 1] = ' ';
            s->result[i] = sum_str[0];
        }
    }

    for (int i = 0; i < max_len_number; i++)
    {
        if (s->result[i] == ' ' || s->result[i] == '0')
        {
            s->result[i] = ' ';
        }
        else
        {
            return;
        }
    }
}

bool sum(struct ListElement **head)
{
    char a[MAX_LENGTH] = {0};
    char b[MAX_LENGTH] = {0};
    char result[MAX_LENGTH] = {0};

    popNumber(head, a);
    popNumber(head, b);

    if (!a[0] || !b[0])
        return false;

    struct MemStruct *s = malloc(sizeof(struct MemStruct));
    if (!s)
        perror("Malloc error");

    int max_len_number;

    max_len_number = strlen(a);
    if (strlen(b) > max_len_number)
        max_len_number = strlen(b);

    resizeString(a, s->a, max_len_number + SIGN_SPACE + 2);
    resizeString(b, s->b, max_len_number + SIGN_SPACE + 2);

    operSum(s);
    s->b[0] = '+';

    printf("%s\n", s->helper);
    printf("%s\n", s->a);
    printf("%s\n", s->b);
    for (int i = 0; i < (max_len_number + SIGN_SPACE + 2); i++)
    {
        putchar('-');
    }
    printf("\n");
    printf("%s\n\n", s->result);

    sprintf(result, "%i", atoi(s->result));
    pushFrontNumber(head, result);

    return true;
}

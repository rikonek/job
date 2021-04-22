#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printHelp(char *argv[])
{
    printf("Usage:\n");
    printf("  %s arg1 arg2 ...\n", argv[0]);
}

typedef struct ListElement
{
    int number;
    struct ListElement *next;
} Node;

bool checkMinNumbers(Node *head)
{
    int counter = 0;
    if (head == NULL)
        return false;
    else
    {
        Node *current = head;
        do
        {
            counter++;
            current = current->next;
        } while (current != NULL);
    }

    if (counter >= 2)
    {
        return true;
    }
    return false;
}

void addNumber(Node **head, int number)
{
    Node *new = malloc(sizeof(Node));
    new->number = number;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        Node *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
    }
}

void addFrontNumber(Node **head, int number)
{
    Node *current = malloc(sizeof(Node));

    current->number = number;
    current->next = (*head);
    *head = current;
}

int popNumber(Node **head)
{
    int number = 0;

    if ((*head) != NULL)
    {
        number = (*head)->number;

        Node *tmp = NULL;

        if (*head != NULL)
        {
            tmp = (*head)->next;
            free(*head);
            *head = tmp;
        }
    }

    return number;
}

bool sum(Node **head)
{
    if (!checkMinNumbers(*head))
    {
        return false;
    }

    int result = popNumber(head) + popNumber(head);
    addFrontNumber(head, result);

    return true;
}

void list(Node *head)
{
    Node *current = head;
    do
    {
        printf("%i", current->number);
        printf("\n");
        current = current->next;
    } while (current != NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printHelp(argv);
        return 0;
    }

    Node *head = NULL;

    for (int i = 1; i < argc; i++)
    {
        addNumber(&head, atoi(argv[i]));
    }

    // list(head);

    int loop = true;
    do
    {
        if (!sum(&head))
        {
            loop = false;
        }
    } while (loop);

    list(head);

    free(head);

    return 0;
}
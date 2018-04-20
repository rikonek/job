#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rstemp-w1.h"
#include "config.h"

unsigned int w1CountDevices()
{
    FILE *fp;
    fp = fopen(W1_COUNT, "r");
    unsigned int count=0;

    if(fp == NULL)
    {
        perror("Error: w1CountDevices");
        return 0;
    }
    else
    {
        fscanf(fp, "%d", &count);
        return count;
    }
}

void w1ReadSensorID(char **sensors)
{
    FILE *fp;
    fp = fopen(W1_SENSORS, "r");
    char line[16];

    if(fp == NULL)
    {
        perror("Error: w1ReadSensorID");
    } 
    else
    {
        unsigned int i=0;
        while(fscanf(fp, "%15s", line) == 1)
        {
            sensors[i] = malloc(16 * sizeof(char));
            strcpy(sensors[i], line);
            i++;
        }
    }
    fclose(fp);
}

int w1ReadTemperature(const char *sensor)
{
    char *url=calloc(200, sizeof(char));
    strcat(url, W1_SENSOR_VALUE_1);
    strcat(url, sensor);
    strcat(url, W1_SENSOR_VALUE_2);

    FILE *fp;
    fp = fopen(url, "r");
    free(url);

    char line[16];
    int temp=0;

    if(fp == NULL)
    {
        perror("Error: w1ReadTemperature");
    } 
    else
    {
        while(fscanf(fp, "%s", line) == 1)
        {
            // printf("Line: %s\n", line);
        }
        if(strstr(line, "t="))
        {
            temp=atoi(line+2);
        }
    }
    fclose(fp);
    return temp;
}
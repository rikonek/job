#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rstemp-w1.h"
#include "config.h"

void w1SetGpio(const unsigned int pin)
{
    FILE *cmd;
    char *pTxt=NULL;
    asprintf(&pTxt, "insmod w1-gpio-custom bus0=0,%d,0", pin);
    cmd=popen(pTxt, "r");
    pclose(cmd);
    free(pTxt);
}

unsigned int w1CountDevices()
{
    unsigned int number_devices=0;
    FILE *fp;
    fp = fopen(W1_COUNT, "r");

    if(fp == NULL)
    {
        perror("Error: w1CountDevices");
    }
    else
    {
        fscanf(fp, "%d", &number_devices);
        fclose(fp);
    }
    return number_devices;
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
        fclose(fp);
    }
}

int w1ReadTemperature(const char *sensor)
{
    // char *url=calloc(200, sizeof(char));
    // strcat(url, W1_SENSOR_VALUE_1);
    // strcat(url, sensor);
    // strcat(url, W1_SENSOR_VALUE_2);

    FILE *fp;
    char *url=NULL;
    asprintf(&url, "%s%s%s", W1_SENSOR_VALUE_1, sensor, W1_SENSOR_VALUE_2);

    fp = fopen(url, "r");
    free(url);

    char line[16];
    int temperature=0;

    if(fp == NULL)
    {
        perror("Error: w1ReadTemperature");
    } 
    else
    {
        while(fscanf(fp, "%s", line) == 1)
        {
            // empty, because I need last line
        }
        if(strstr(line, TEMPERATURE_PARSE_STRING)) // I need last line in format "t=23674"
        {
            temperature=atoi(line+2); // move start index from 0 to 2 (remove "t=")
        }
        fclose(fp);
    }
    return temperature;
}
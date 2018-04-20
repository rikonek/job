#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "rstemp-w1.h"

int main()
{
    printf("RS Temp\n");

    unsigned int w1count = w1CountDevices();
    printf("Found devices: %d\n", w1count);

    if(w1count > 0)
    {
        char *sensors[w1count];

        w1ReadSensorID(sensors);

        for(unsigned int i=0; i<w1count; i++)
        {
            int temp=w1ReadTemperature(sensors[i]);
            printf("Sensor ID: %s, value: %d, temperature: %.1f\n", sensors[i], temp, (float) temp/1000);
            free(sensors[i]);
        }
    }


    return 0;
}
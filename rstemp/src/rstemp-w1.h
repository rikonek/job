#ifndef _RSTEMP_W1_H_

#define _RSTEMP_W1_H_

#define TEMPERATURE_PARSE_STRING "t="

void w1SetGpio(const unsigned int);
unsigned int w1CountDevices();
void w1ReadSensorID(char **);
int w1ReadTemperature(const char *);

#endif
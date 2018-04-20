#ifndef _RSTEMP_W1_H_

#define _RSTEMP_W1_H_

unsigned int w1CountDevices();
void w1ReadSensorID(char **);
int w1ReadTemperature(const char *);

#endif
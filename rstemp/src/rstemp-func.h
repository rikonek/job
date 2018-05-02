#include <stdbool.h>

#ifndef _RSTEMP_FUNC_H

#define _RSTEMP_FUNC_H

typedef struct config
{
    unsigned int sleep_time;
    unsigned int repeat;
    bool clear_lcd;
} config_t;

void printHelp(const char *);
void setConfigClearLCD(config_t *, bool);
void setConfigRepeat(config_t *, int);
void setConfigSleepTime(config_t *, int);
int parseCmdOption(int, char *[], config_t *);
void run(const config_t *);

#endif
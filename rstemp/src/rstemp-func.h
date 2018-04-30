#include <stdbool.h>

#ifndef _RSTEMP_FUNC_H

#define _RSTEMP_FUNC_H

struct config
{
    unsigned int sleep_time;
    unsigned int repeat;
    bool clear_lcd;
};

void printHelp(const char *);
void setConfigClearLCD(struct config *, bool);
void setConfigRepeat(struct config *, int);
void setConfigSleepTime(struct config *, int);
int parseCmdOption(int, char *[], struct config *);
void run(const struct config *);

#endif
#include "rstemp-func.h"
#include "config.h"

int main(int argc, char *argv[])
{
    config_t cfg = { MIN_SLEEP_TIME, DEFAULT_REPEAT, DEFAULT_CLEAR_LCD };

    if(parseCmdOption(argc, argv, &cfg) == 0) return 0;

    run(&cfg);

    return 0;
}
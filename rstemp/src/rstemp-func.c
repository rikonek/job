#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

#include "rstemp-func.h"
#include "rstemp-lcd.h"
#include "rstemp-w1.h"
#include "config.h"

void printHelp(const char *name)
{
    printf("RS Temp\n\n");
    printf("NAME\n");
    printf("\trstemp - read 1-wire temperature and display on LCD");
    printf("\n\n");
    printf("SYNOPSIS\n");
    printf("\t%s [options]\n", name);
    printf("\n\n");
    printf("OPTIONS\n");
    #if !DEFAULT_CLEAR_LCD
        printf("\t-c, --clear\n\t\tClear LCD.\n\n");
    #endif
    printf("\t-n\n\t\tRepeat n-times. Set 0 for never ending.\n\n");
    printf("\t-s, --sleep=[time in seconds]\n\t\tSleep time between readings.\n\n");
    printf("\t-w, --w1=[gpio pin]\n\t\tInitialize w1 on gpio pin.\n\n");
}

void setConfigClearLCD(struct config *cfg, bool flag)
{
    cfg->clear_lcd=flag;
}

void setConfigRepeat(struct config *cfg, int n)
{
    if(n<0)
    {
        n=0;
    }
    cfg->repeat=n;
}

void setConfigSleepTime(struct config *cfg, int time)
{
    if(time<MIN_SLEEP_TIME)
    {
        time=MIN_SLEEP_TIME;
        printf("Set default sleep time: %d\n", time);
    }
    if(time>MAX_SLEEP_TIME)
    {
        time=MAX_SLEEP_TIME;
    }
    cfg->sleep_time=time;
}

int parseCmdOption(int argc, char *argv[], struct config *cfg)
{
    static struct option long_options[] = {
        {"clear", no_argument,       0, 'c' },
        {"help",  no_argument,       0, 'h' },
        {"sleep", required_argument, 0, 's' },
        {"w1",    required_argument, 0, 'w' },
        {0,       0,                 0, 0 }
    };

    int param;
    while((param = getopt_long(argc, argv, "chn:s:w:", long_options, NULL)) != -1)
    {
        switch(param)
        {
            case 'c': // clear
                setConfigClearLCD(cfg, true);
                break;

            case 'h': // help
                printHelp(argv[0]);
                return 0;
                break;

            case 'n': // n-times repeat
                setConfigRepeat(cfg, atoi(optarg));
                break;

            case 's': // sleep
                setConfigSleepTime(cfg, atoi(optarg));
                break;

            case 'w': // w1
                w1SetGpio(atoi(optarg));
                return 0;
                break;

            default:
                printf("Try help:\n\t%s --help\n", argv[0]);
                return 0;
                break;
        }
    }
    return 1;
}

void run(const struct config *cfg)
{
    const unsigned int w1count = w1CountDevices();
    printf("Found devices: %d\n", w1count);

    if(w1count > 0)
    {
        char *sensors[w1count];
        int sensors_val[w1count];
        int sensors_avg=0;
        int lcd_fd=lcdInit();

        lcdCursorOff(lcd_fd);
        lcdClear(lcd_fd);

        char *pTxt=NULL;
        unsigned int line=1;
        unsigned int position=0;

        w1ReadSensorID(sensors);

        unsigned int loop_count=1;

        while(1)
        {
            if(cfg->clear_lcd)
            {
                lcdClear(lcd_fd);
            }
            sensors_avg=0;
            for(unsigned int i=0; i<w1count; i++)
            {
                sensors_val[i]=w1ReadTemperature(sensors[i]);
                sensors_avg+=sensors_val[i];
                printf("Sensor ID: %s, value: %d, temperature: %.1f\n", sensors[i], sensors_val[i], (float) sensors_val[i]/1000);
                asprintf(&pTxt, "T%d:%.1f", i+1, (float) sensors_val[i]/1000);
                line=(i/2)+1;
                if(line>2) line=1;
                position=i%2*8;
                lcdPrint(lcd_fd, line, position, pTxt);
            }

            printf("                    Average value: %d, temperature: %.1f\n", sensors_avg/w1count, (float) sensors_avg/w1count/1000);
            asprintf(&pTxt, "AV:%.1f", (float) sensors_avg/w1count/1000);
            lcdPrint(lcd_fd, 2, 8, pTxt);

            if(cfg->repeat>0 && loop_count>=cfg->repeat)
            {
                break;
            }
            loop_count++;
            sleep(cfg->sleep_time);
        }
        for(unsigned int i=0; i<w1count; i++)
        {
            free(sensors[i]);
        }
        free(pTxt);
        lcdDeInit(lcd_fd);
    }
}
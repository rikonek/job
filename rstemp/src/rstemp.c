#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include "rstemp-w1.h"
#include "rstemp-lcd.h"

int main(int argc, char *argv[])
{
    printf("RS Temp\n");

    if(argc>1)
    {
        if(strcmp(argv[1], "--help") == 0)
        {
            printf("Usage: %s [option]\n", argv[0]);
            printf("  read\t\t\tRead w1, clear and display on LCD\n");
            printf("  refresh [time in seconds]\t\tRefresh w1 on LCD\n");
            printf("  w1 [gpio pin]\t\tInitialize w1 on gpio pin\n");
            return 0;
        }
        if(strcmp(argv[1], "read") == 0 || strcmp(argv[1], "refresh") == 0)
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

                if(strcmp(argv[1], "read") == 0)
                {
                    lcdClear(lcd_fd);
                }
                char *pTxt=NULL;
                unsigned int line=1;
                unsigned int position=0;

                w1ReadSensorID(sensors);

                unsigned int loop=1;
                unsigned int time=10;
                if(argc>2)
                {
                    time=atoi(argv[2]);
                    if(time<10) time=10;
                }
                while(loop)
                {
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
                        usleep(100000);
                    }

                    printf("                    Average value: %d, temperature: %.1f\n", sensors_avg/w1count, (float) sensors_avg/w1count/1000);
                    asprintf(&pTxt, "AV:%.1f", (float) sensors_avg/w1count/1000);
                    lcdPrint(lcd_fd, 2, 8, pTxt);

                    if(strcmp(argv[1], "refresh") == 0)
                    {
                        sleep(time);
                    }
                    else
                    {
                        loop=0;
                    }
                }
                for(unsigned int i=0; i<w1count; i++)
                {
                    free(sensors[i]);
                }
                free(pTxt);
                lcdDeInit(lcd_fd);
            }
        }
        if(argc>2 && strcmp(argv[1], "w1") == 0)
        {
            FILE *cmd;
            char *pTxt=NULL;
            asprintf(&pTxt, "insmod w1-gpio-custom bus0=0,%d,0", atoi(argv[2]));
            cmd=popen(pTxt, "r");
            pclose(cmd);
            free(pTxt);
        }
    }
    else
    {
        printf("Try help: %s --help\n", argv[0]);
        return 0;
    }

    return 0;
}
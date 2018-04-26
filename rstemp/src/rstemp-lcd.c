#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "rstemp-lcd.h"
#include "config.h"

int lcdInit()
{
    int lcd = open(LCD_DEV, O_WRONLY | O_NDELAY);
	if(lcd < 0)
    {
        perror("Error: lcdInit");
	}
    return lcd;
}

void lcdDeInit(int lcd_fd)
{
    if(lcd_fd < 0) return;
    
    close(lcd_fd);
}

void lcdClear(int lcd_fd)
{
    if(lcd_fd < 0) return;

    struct ioctl_mesg msg;

    if(ioctl(lcd_fd, (unsigned int) IOCTL_CLEAR_DISPLAY, &msg) < 0)
    {
        perror("Error: lcdClear");
    }
}

void lcdPrint(int lcd_fd, unsigned int line, unsigned int position, char txt[])
{
    if(lcd_fd < 0) return;

    struct ioctl_mesg msg;

	memset(msg.kbuf, '\0', sizeof(char) * MAX_BUF_LENGTH);
	strncpy(msg.kbuf, txt, MAX_BUF_LENGTH);
	msg.kbuf[MAX_BUF_LENGTH-1] = '\0';
	msg.lineNumber=line;
	msg.nthCharacter=position;

    if(ioctl(lcd_fd, (unsigned int) IOCTL_PRINT_WITH_POSITION, &msg) < 0)
    {
        perror("Error: lcdPrint");
    }
}

void lcdCursorOff(int lcd_fd)
{
    if(lcd_fd < 0) return;

    struct ioctl_mesg msg;
    if(ioctl(lcd_fd, (unsigned int) IOCTL_CURSOR_OFF, &msg) < 0)
    {
        perror("Error: lcdCursorOff");
    }
}
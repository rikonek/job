#ifndef _RSTEMP_LCD_H_

#define _RSTEMP_LCD_H_

#include <linux/ioctl.h>

// ******************* KLCD Settings *******************

#define MAX_BUF_LENGTH  	50  /* maximum length of a buffer to copy from user space to kernel space (MUST NOT CHANGE THIS) */
struct ioctl_mesg{
	char kbuf[MAX_BUF_LENGTH];	// a string to be printed on the LCD

	unsigned int lineNumber;	// line number (should be either 1 or 2)
	unsigned int nthCharacter;	// nth Character of a line (0 refers to the beginning of the line)
};

// ******************* IOCTL COMMAND ARGUMENTS *******************

#define IOCTL_CLEAR_DISPLAY 	  	'0'   // Identifiers for ioctl reqursts
#define IOCTL_PRINT_ON_FIRSTLINE  	'1'
#define IOCTL_PRINT_ON_SECONDLINE 	'2'	/* (Note) ioctl will not be called if this is unsigned int 2, which is a reserved number. Thus it is fixed to '2' */
#define IOCTL_PRINT_WITH_POSITION 	'3'
#define IOCTL_CURSOR_ON			'4'
#define IOCTL_CURSOR_OFF		'5'

// ******************* PROTOTYPE *******************

int lcdInit();
void lcdDeInit(int);
void lcdClear(int);
void lcdPrint(int, unsigned int, unsigned int, char []);
void lcdCursorOff(int);

#endif
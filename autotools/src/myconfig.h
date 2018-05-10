#ifndef _MYCONFIG_H_
#define _MYCONFIG_H_

#define CFG_NAME "default"

#ifdef _DEV_
    #undef CFG_NAME
    #define CFG_NAME "DEVELOPER"
#endif


#endif
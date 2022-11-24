#ifndef _LED_H_
#define _LED_H_
#include <fcntl.h>
int ledStatus(void);
int ledOnOff (int ledNum, int onOff);
int ledLibInit(void);
int ledLibExit(void);

#define LED_DRIVER_NAME "/dev/periled"

#endif _LED_H_
#ifndef _COLORLED_H_
#define _COLORLED_H_
int pwmLedInit(void);
int pwmActiveAll(void);
int pwmInactiveAll(void);
int pwmSetDuty(int dutyCycle, int pwmIndex);
int pwmSetPeriod(int Period, int pwmIndex);
int pwmSetPercent( int percent , int ledColor);
int pwmStartAll(void);

#endif

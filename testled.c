#include "led.h"

int main(void)
{
    ledLibInit();
    ledOnOff(0,1);
    sleep(1);
    ledOnOff(1,1);
    sleep(1);
    ledOnOff(2,1);
    sleep(1);
    ledOnOff(3,1);
    sleep(1);
    ledOnOff(4,1);
    sleep(1);
    ledOnOff(5,1);
    sleep(1);
    ledOnOff(6,1);
    sleep(1);
    ledOnOff(7,1);
    sleep(1);
    ledLibExit();
    return 0;
}
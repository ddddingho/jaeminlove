#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "gyro.h"

int main (void)
{
    Accel();
    sleep(1);
    Mag();
    sleep(1);
    Gyro();
    return 0;
}

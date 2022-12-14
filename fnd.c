#include "fnd.h"

int fndDisp(int num, int dotflag)
{
    int fd;
    int temp,i;
    stFndWiteForm stWriteData;
    for(i=0; i<MAX_FND_NUM; i++)
    {
        stWriteData.DataDot[i] = (dotflag&(0x1 <<i))?1 : 0; //dot켜진 부분 1
        stWriteData.DataValid[i] = 1;
    }

    // if 6fnd
    temp = num % 1000000; stWriteData.DataNumeric[0] = temp/100000;
    temp = num % 100000; stWriteData.DataNumeric[1] = temp/10000;
    temp = num % 10000; stWriteData.DataNumeric[2] = temp/1000;
    temp = num % 1000; stWriteData.DataNumeric[3] = temp/100;
    temp = num % 100; stWriteData.DataNumeric[4] = temp/10;
    stWriteData.DataNumeric[5] = num %10;
    fd = open(FND_DRIVER_NAME,O_RDWR); // /dev/perifnd를 read형태로 open
    if (fd<0)
    {
        perror("driver open error.\n");
        return 0;
    }
    write(fd, &stWriteData,sizeof(stFndWiteForm)); //stwritedata내용을 fd에 씀
    close(fd);
    return 1;
}
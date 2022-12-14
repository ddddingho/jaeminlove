#ifndef _FND_DRV_H_
#define _FND_DRV_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM +2)
#define FND_DRIVER_NAME "/dev/perifnd"


typedef struct FNDWriteDataForm_tag
{
    char DataNumeric[FND_DATA_BUFF_LEN];
    char DataDot[FND_DATA_BUFF_LEN];
    char DataValid[FND_DATA_BUFF_LEN];

}stFndWiteForm,*pStFndWriteForm;

int fndDisp(int num, int dotflag);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "touch.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"WaveShare WaveShare Touchscreen\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=mouse0 event"

static int fp;
static int readSize, inputIndex;
static struct input_event stEvent;
static char touchPath[200] = {0,};
static int exit_pth = 0; // exit 신호 for thread
static pthread_t touchTh_id;
static int msgID;


int probeTouchPath(char *newPath)

{
	int returnValue = 0;
	int number = 0;
	FILE *fp = fopen(PROBE_FILE, "rt");

	while (!feof(fp)) //끝까지 읽어들인다.
	{
		char tmpStr[200];		// 200자를 읽을 수 있게 버퍼
		fgets(tmpStr, 200, fp); //최대 200자를 읽어봄
								// printf ("%s",tmpStr);

		if (strcmp(tmpStr, HAVE_TO_FIND_1) == 0)
		{
			printf("touch : YES! I found!: %s\r\n", tmpStr);
			returnValue = 1; //찾음
		}

		if ((returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0)) //찾은 상태에서Event??을 찾았으면
		{
			printf("-->%s", tmpStr);
			printf("\t%c\r\n", tmpStr[strlen(tmpStr) - 3]);
			number = tmpStr[strlen(tmpStr) - 3] - '0';
			// Ascii character '0'-'9' (0x30-0x39)
			// to interger(0)
			break;
		}
	}
	fclose(fp);

	if (returnValue == 1)
		sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
	return returnValue;
};

void *touchThFunc(void *arg);

int touchInit(void)
{
	if (probeTouchPath(touchPath) == 0)
	{
		return 0;
	}

	msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);
	fp = open(touchPath, O_RDONLY);

	int err = pthread_create(&touchTh_id, NULL, &touchThFunc, NULL);
	int a = pthread_detach(touchTh_id);

	if (a == 1)
	{
		printf("touch : error of detaching thread\r\n");
	}

	return 1;
};

void *touchThFunc(void *arg)
{
	int x = 0;
	int y = 0;
	TOUCH_MSG_T send;
	send.messageNum = 1;
	send.keyInput = 999;
	while (1)
	{
		 read(fp, &stEvent, sizeof(stEvent));

           if (stEvent.type == EV_ABS)
	   {
		//뭔가 좌표값이 들어올 것만 같다.
		if(stEvent.code == ABS_MT_POSITION_X)
		{
			x = stEvent.value;
			//printf("you touch X : %d\r\n", stEvent.value);
		}
		else if(stEvent.code == ABS_MT_POSITION_Y)
                {
			y = stEvent.value;
                  //      printf("you touch Y : %d\r\n", stEvent.value);
                }
	   }
	else if( (stEvent.type == EV_KEY) && (stEvent.code==BTN_TOUCH) )
	{
		send.x = x;
		send.y = y;
		if(stEvent.value == 0)
		{
			send.pressed = 0;
		//printf("you finished Touch!\r\n");
		//좌표 입력이 끝났다.

		}
		else if (stEvent.value == 1)
		{
			send.pressed = 1;
			//printf("you touch Now!\r\n");
		}
		msgsnd(msgID, &send, sizeof(TOUCH_MSG_T) - sizeof(long int), 0);

	}
}

}


int touchExit(void)
{
	exit_pth = 1;
	close(fp);
}

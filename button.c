#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static int fp;
static int readSize, inputIndex;
static struct input_event stEvent;
static char buttonPath[200] = {
	0,
};
static int exit_pth = 0; // exit 신호 for thread
static pthread_t buttonTh_id;
static int msgID;

BUTTON_MSG_T send;

int probeButtonPath(char *newPath)

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
			printf("button : YES! I found!: %s\r\n", tmpStr);
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

int buttonInit(void)
{
	if (probeButtonPath(buttonPath) == 0)
	{
		return 0;
	}
	printf("button : msgget start\r\n");
	msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
	printf("button : msgget success\r\n");
	fp = open(buttonPath, O_RDONLY);

	int err = pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL);
	int a = pthread_detach(buttonTh_id);

	if (a == 1)
	{
		printf("button : error of detaching thread\r\n");
	}

	printf("buttoninit success finish\r\n");
	return 1;
};

void *buttonThFunc(void *arg)
{
	while (1)
	{
		printf("button function start \r\n");
		send.messageNum = 1;

		//입력이 들어와야 read를 한
		printf("read start\r\n");
		readSize = read(fp, &stEvent, sizeof(stEvent));

		if (readSize != sizeof(stEvent))
		{
			continue;
		}
		printf("read success\r\n");

		if (exit_pth == 1)
		{
			pthread_exit(0);
		}
		printf("pthread_exit success\r\n");


		printf("waiting key input\r\n");
		if (stEvent.type == EV_KEY)
		{
			switch (stEvent.code)
			{
			/*
			case KEY_VOLUMEUP:
				send.keyInput = 1;
				msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
				printf("button : msgsnd 1 success\r\n");
				break;

			case KEY_HOME:
				send.keyInput = 2;
				msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
				printf("button : msgsnd 2 success\r\n");
				break;
			*/

			//buttonInit();
			case KEY_SEARCH:
				send.keyInput = 1;
				msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
				printf("button : msgsnd 1 success\r\n");
				break;

			case KEY_BACK:
				send.keyInput = 2;
				msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
				printf("keyInput : msgsnd 2 success\r\n");
				break;

			/*
			case KEY_MENU:
				send.keyInput = 5;
				msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
				printf("button : msgsnd 5 success\r\n");
				break;

			case KEY_VOLUMEDOWN:
				send.keyInput = 6;
				msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
				printf("button : msgsnd 6 success\r\n");
				break;
				*/
			}

			// 아직안씀
			/*
			if (stEvent.value)

			{
				send.pressed = 1;
				msgsnd(msgID, &send.pressed, sizeof(send.pressed), 0);
			}

			else
			{
				send.pressed = 3;
				msgsnd(msgID, &send.pressed, sizeof(send.pressed), 0);
				printf("\n");
			} // End of if
			*/
		}

		else  // EV_SYN
			; // do notthing
		printf("key input finish\r\n");
	}		  // End of While

	close(fp);
}

int buttonExit(void)
{
	exit_pth = 1;
	close(fp);
};
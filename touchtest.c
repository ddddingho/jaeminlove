#include "touch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include <sys/ipc.h>

int main(void)
{
	touchInit();
	int msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);
	TOUCH_MSG_T recv;
	while(1){
		msgrcv(msgID, &recv, sizeof(recv)-sizeof(long int), 0, 0);
		//이때는 터치가 일어나거나 아니면 터치가 끝날때만 여기에 들어옴
	
	switch(recv.keyInput)
	{
		case 999:
			if(recv.pressed == 1)
		{
			if(recv.x >= 0 && recv.x <205 && recv.y >=401 && recv.y<601)
			{
				system("aplay ./pianodo");
			}

			else if(recv.x >= 0 && recv.x <205 && recv.y >=201 && recv.y<401)
                        {
				system("aplay ./pianore");
                        }

			else if(recv.x >= 0 && recv.x <205 && recv.y >=0 && recv.y<201)
                        {
				system("aplay ./pianomi");
                        }

                        else if(recv.x >= 205 && recv.x <410 && recv.y >=401 && recv.y<601)
                        {
				system("aplay ./pianofa");
                        }
             
	     		else if(recv.x >= 205 && recv.x <410 && recv.y >=201 && recv.y<401)
                        {
				system("aplay ./pianosol");
                        }
             
	     		else if(recv.x >= 205 && recv.x <410 && recv.y >=0 && recv.y<201)
                        {
				system("aplay ./pianora");
                        }

                        else if(recv.x >= 410 && recv.x <615 && recv.y >=401 && recv.y<601)
                        {
				system("aplay ./pianosi");
                        }

                        else if(recv.x >= 410 && recv.x <615 && recv.y >=201 && recv.y<401)
                        {
				system("aplay ./pianohighdo");
                        }

                        else if(recv.x >= 410 && recv.x <615 && recv.y >=0 && recv.y<201)
                        {
				system("aplay ./pianohighre");
                        }

                        else if(recv.x >= 615 && recv.x <820 && recv.y >=401 && recv.y<601)
                        {
				system("aplay ./pianohighmi");
                        }

                        else if(recv.x >= 615 && recv.x <820 && recv.y >=201 && recv.y<401)
                        {
				system("aplay ./pianohighfa");
                        }

                        else if(recv.x >= 615 && recv.x <820 && recv.y >=0 && recv.y<201)
                        {
				system("aplay ./pianohighsol");
                        }

                        else if(recv.x >= 819 && recv.x <1025 && recv.y >=401 && recv.y<601)
                        {
				system("aplay ./pianohighra");
                        }

                        else if(recv.x >= 819 && recv.x <1025 && recv.y >=201 && recv.y<401)
                        {
				system("aplay ./pianohighsi");
                        }

                        else if(recv.x >= 819 && recv.x <1025 && recv.y >=0 && recv.y<201)
                        {
				system("aplay ./pianohighhighdo");
                        }

		break;
		}
}
}
}

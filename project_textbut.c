#include "textlcd.h"
#include "button.h"
#include "led.h"
#include "fnd.h"
#include "touch.h"
int main(void)
{
   unsigned int linenum = 0;
   stTextLCD stlcd;
   int keycheck;
   int fd;
   int len;
   int number;
   memset(&stlcd, 0, sizeof(stTextLCD));
   lcdtextwrite("===== MENU =====", 0, 1);
   lcdtextwrite(0, "You can use 5key", 2);

   // button
   printf("button start1\r\n");
   BUTTON_MSG_T rcv;

   int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);

   printf("message get success\r\n");

   ledLibInit();

   // 초기화
   ledOnOff(0, 0);
   ledOnOff(1, 0);
   ledOnOff(2, 0);
   ledOnOff(3, 0);
   ledOnOff(4, 0);
   ledOnOff(5, 0);
   ledOnOff(6, 0);

   buttonInit();
   // touch
   touchInit();
   TOUCH_MSG_T recv;

   char *buf[100][200];
   int i = 0;
   int k = 0;

   // printf("button start2 - case\r\n");
   // printf("pwmleditit start\r\n");
   // pwmLedInit();
   // printf("pwmleditit finish\r\n");
   // printf("\r\n");
   // printf("pwmsetpercent1 start\r\n");
   // pwmSetPercent(100, 0);
   // sleep(3);
   // printf("pwmsetpercent1 stop\r\n");
   // printf("pwmsetpercent2 start\r\n");
   // pwmSetPercent(0, 1);
   // sleep(3);

   // printf("pwmsetpercent2 start\r\n");

   // printf("pwmincativeall start\r\n");
   // pwmInactiveAll();

   // printf("pwmincativeall stop\r\n");
   // printf("\r\n");
   // fnd
   typedef struct tm_t
   {
      int tm_hour;
      int tm_min;
      int tm_sec;
   } TM_T;
   // struct tm_t * ptmcur;
   TM_T *ptmcur;

   time_t tTime;

   while (1)
   {

      msgrcv(msgID, &rcv.keyInput, sizeof(rcv.keyInput), 0, 0);
      printf("receive the MESSAGE ! \r\n");
      msgrcv(msgID, &recv, sizeof(recv) - sizeof(long int), 0, 0);
      printf("receive the touch message!\r\n");

      switch (rcv.keyInput)
      {

      case (1):
         printf("\r\nTEXTLCD -  PIANO/DRUM/GUITAR \r\n");
         lcdtextwrite("      PIANO     ", 0, 1);
         lcdtextwrite(0, " DRUM    GUITAR ", 2);
         ledOnOff(1, 1);
         ledOnOff(2, 0);
         ledOnOff(3, 0);
         ledOnOff(4, 0);
         ledOnOff(5, 0);
         ledOnOff(6, 0);
         // color LED
         //  pwmSetPercent(100,i);
         //  if(i==2) i = 0;
         //  else i = i+1;
         // fnd
         ptmcur = localtime(&tTime);

         number = ptmcur->tm_hour * 10000;
         number += ptmcur->tm_min * 100;
         number += ptmcur->tm_sec;

         fndDisp(number, 0b1010);

         keycheck = 1;
         break;

      case (2):
         printf("\r\nTEXTLCD - UP\r\n");
         lcdtextwrite("LINE 1       O  ", 0, 1);
         lcdtextwrite(0, "LINE 2          ", 2);
         ledOnOff(1, 1);
         ledOnOff(2, 1);
         ledOnOff(3, 0);
         ledOnOff(4, 0);
         ledOnOff(5, 0);
         ledOnOff(6, 0);
         keycheck = 2;
         break;

      case (3):
         printf("\r\nTEXTLCD -  DOWN \r\n");
         lcdtextwrite("LINE 1          ", 0, 1);
         lcdtextwrite(0, "LINE 2       O  ", 2);
         ledOnOff(1, 1);
         ledOnOff(2, 1);
         ledOnOff(3, 1);
         ledOnOff(4, 0);
         ledOnOff(5, 0);
         ledOnOff(6, 0);
         keycheck = 3;
         break;

      case (4):
         printf("\r\nTEXTLCD - SELECT\r\n");
         if (keycheck == 2)
         {
            lcdtextwrite("-----SELECT-----", 0, 1);
            lcdtextwrite(0, " LINE 1 SELECT  ", 2);
         }
         else if (keycheck == 3)
         {
            lcdtextwrite("-----SELECT-----", 0, 1);
            lcdtextwrite(0, " LINE 2 SELECT  ", 2);
         }
         ledOnOff(1, 1);
         ledOnOff(2, 1);
         ledOnOff(3, 1);
         ledOnOff(4, 1);
         ledOnOff(5, 0);
         ledOnOff(6, 0);
         keycheck = 4;
         break;

      case (5):
         printf("\r\nTEXTLCD -  BACK \r\n");
         {
            lcdtextwrite("      BACK      ", 0, 1);
            lcdtextwrite(0, "                ", 2);
         }
         ledOnOff(1, 1);
         ledOnOff(2, 1);
         ledOnOff(3, 1);
         ledOnOff(4, 1);
         ledOnOff(5, 1);
         ledOnOff(6, 0);
         keycheck = 5;
         break;
      case (6):
         printf("\r\nTEXTLCD - NONE\r\n");
         ledOnOff(1, 1);
         ledOnOff(2, 1);
         ledOnOff(3, 1);
         ledOnOff(4, 1);
         ledOnOff(5, 1);
         ledOnOff(6, 1);
         keycheck = 6;
         break;
      }
   }

   switch (recv.keyInput)
   {
   case 999:
      if (recv.pressed == 1)
      {
         if (recv.x >= 0 && recv.x < 205 && recv.y >= 401 && recv.y < 601)
         {
            system("aplay ./pianodo");
            sprintf(buf[i], "aplay ./pianodo");
         }

         else if (recv.x >= 0 && recv.x < 205 && recv.y >= 201 && recv.y < 401)
         {
            system("aplay ./pianore");
            sprintf(buf[i], "aplay ./pianore");
         }

         else if (recv.x >= 0 && recv.x < 205 && recv.y >= 0 && recv.y < 201)
         {
            system("aplay ./pianomi");
            sprintf(buf[i], "aplay ./pianomi");
         }

         else if (recv.x >= 205 && recv.x < 410 && recv.y >= 401 && recv.y < 601)
         {
            system("aplay ./pianofa");
            sprintf(buf[i], "aplay ./pianofa");
         }

         else if (recv.x >= 205 && recv.x < 410 && recv.y >= 201 && recv.y < 401)
         {
            system("aplay ./pianosol");
            sprintf(buf[i], "aplay ./pianosol");
         }

         else if (recv.x >= 205 && recv.x < 410 && recv.y >= 0 && recv.y < 201)
         {

            system("aplay ./pianora");
            sprintf(buf[i], "aplay ./pianora");
         }

         else if (recv.x >= 410 && recv.x < 615 && recv.y >= 401 && recv.y < 601)
         {

            system("aplay ./pianosi");
            sprintf(buf[i], "aplay ./pianosi");
         }

         else if (recv.x >= 410 && recv.x < 615 && recv.y >= 201 && recv.y < 401)
         {
            system("aplay ./pianohighdo");
            sprintf(buf[i], "aplay ./pianohighdo");
         }

         else if (recv.x >= 410 && recv.x < 615 && recv.y >= 0 && recv.y < 201)
         {
            system("aplay ./pianohighre");
            sprintf(buf[i], "aplay ./pianohighre");
         }

         else if (recv.x >= 615 && recv.x < 820 && recv.y >= 401 && recv.y < 601)
         {
            system("aplay ./pianohighmi");
            sprintf(buf[i], "aplay ./pianohighmi");
         }

         else if (recv.x >= 615 && recv.x < 820 && recv.y >= 201 && recv.y < 401)
         {
            system("aplay ./pianohighfa");
            sprintf(buf[i], "aplay ./pianohighfa");
         }

         else if (recv.x >= 615 && recv.x < 820 && recv.y >= 0 && recv.y < 201)
         {
            system("aplay ./pianohighsol");
            sprintf(buf[i], "aplay ./pianohighsol");
         }

         else if (recv.x >= 819 && recv.x < 1025 && recv.y >= 401 && recv.y < 601)
         {
            system("aplay ./pianohighra");
            sprintf(buf[i], "aplay ./pianohighra");
         }

         else if (recv.x >= 819 && recv.x < 1025 && recv.y >= 201 && recv.y < 401)
         {
            for (k = 0; k <= i; k++)
            {

               system(buf[k]);
               printf("system %d\r\n", k);
            }
            // system("aplay ./pianohighsi");
            // sprintf(buf[i],"aplay ./pianohighsi");
         }

         else if (recv.x >= 819 && recv.x < 1025 && recv.y >= 0 && recv.y < 201) // 버퍼값 초기화.
         {
            // system("aplay ./pianohighhighdo");
            for (k = 0; k <= i; k++)
            {
               memset(buf, 0x00, sizeof(buf)); // str 이라는 변수안의 값을 모두 0x00( 널 ) 으로 초기화
            }
         }
         i++;
         break;
      }

      buttonExit();
      ledLibExit();
      return 0;
   }
}

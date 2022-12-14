#include "textlcd.h"
#include "button.h"
#include "colorled.h"
#include "fnd.h"

int main(void)
{
    unsigned int linenum = 0;
    stTextLCD stlcd;
    int keycheck ;
    int fd;
    int len;
    int i;
    memset(&stlcd,0,sizeof(stTextLCD));
    lcdtextwrite("line 1", 0, 1);
    lcdtextwrite(0, "line 2", 2);
   pwmLedInit();
    //button
    printf("button start1\r\n");
    BUTTON_MSG_T rcv;

   int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);


    printf("message get success\r\n");
    
    buttonInit();
    printf("button start2 - case\r\n");

    //fnd
    int number;
        //struct tm *ptmcur;
        
    

    
   while(1){
      //fnd
      typedef struct tm_t
        {
            int tm_hour;
            int tm_min;
            int tm_sec;
        } TM_T;
        //struct tm_t * ptmcur;
        TM_T *ptmcur;

        time_t tTime;
        if(time(&tTime) == -1)
        {
            return -1;
        }
            

        ptmcur = localtime(&tTime);

        number = ptmcur -> tm_hour * 10000;
        number += ptmcur ->tm_min *100;
        number += ptmcur -> tm_sec;

        fndDisp(number,0b1010);
        //
      msgrcv(msgID,&rcv.keyInput,sizeof(rcv.keyInput),0,0);
        printf("receive the MESSAGE ! \r\n");
        

      switch(rcv.keyInput){

            case(1): printf("\r\nTEXTLCD -  PIANO/DRUM/GUITAR \r\n"); 
                     lcdtextwrite("     PIANO     ",0,1);
                     lcdtextwrite(0," DRUM    GUITAR ",2);
                     pwmSetPercent(100,i);
                     if(i==2) i = 0;
                     else i = i+1;
                     keycheck = 1;
                     break;

          case(2): printf("\r\nTEXTLCD - UP\r\n"); 
                     lcdtextwrite("LINE 1       O ",0,1);
                     lcdtextwrite(0,"LINE 2       ",2);
                     keycheck = 2;
                     break;
            
         case(3): printf("\r\nTEXTLCD -  DOWN \r\n"); 
                     lcdtextwrite("LINE 1         ",0,1);
                     lcdtextwrite(0,"LINE 2       O ",2);
                     keycheck = 3;
                     break;

          case(4): printf("\r\nTEXTLCD - SELECT\r\n"); 
                     if(keycheck == 2)
                     {
                        lcdtextwrite("-----SELECT-----",0,1);
                        lcdtextwrite(0," LINE 1 SELECT  ",2);
                     }
                     else if (keycheck == 3)
                     {
                        lcdtextwrite("-----SELECT-----",0,1);
                        lcdtextwrite(0," LINE 2 SELECT  ",2);
                     }
                     keycheck = 4;
                     break;
                     
            case(5): printf("\r\nTEXTLCD -  BACK \r\n"); 
                    {
                        lcdtextwrite("      BACK      ",0,1);
                        lcdtextwrite(0,"                ",2);
                     }
          case(6): printf("\r\nTEXTLCD - NONE\r\n"); 
                     keycheck = 6;
                     break;
      }
      }

        buttonExit();
    return 0;

    }
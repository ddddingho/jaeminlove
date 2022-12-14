#include "textlcd.h"
#include "button.h"

int main(void)
{
    unsigned int linenum = 0;
    stTextLCD stlcd;
    int keycheck ;
    int fd;
    int len;
    memset(&stlcd,0,sizeof(stTextLCD));
    lcdtextwrite("===== MENU =====", 0, 1);
    lcdtextwrite(0, "You can use 5key", 2);

    //button
    printf("button start1\r\n");
    BUTTON_MSG_T rcv;

	int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);


    printf("message get success\r\n");
    
    buttonInit();
    printf("button start2 - case\r\n");

    
	while(1){

		msgrcv(msgID,&rcv.keyInput,sizeof(rcv.keyInput),0,0);
        printf("receive the MESSAGE ! \r\n");
        

		switch(rcv.keyInput){

            case(1): printf("\r\nTEXTLCD -  PIANO/DRUM/GUITAR \r\n"); 
                     lcdtextwrite("      PIANO     ",0,1);
                     lcdtextwrite(0," DRUM    GUITAR ",2);
                     keycheck = 1;
                     break;

		    case(2): printf("\r\nTEXTLCD - UP\r\n"); 
                     lcdtextwrite("LINE 1       O  ",0,1);
                     lcdtextwrite(0,"LINE 2          ",2);
                     keycheck = 2;
                     break;
            
			case(3): printf("\r\nTEXTLCD -  DOWN \r\n"); 
                     lcdtextwrite("LINE 1          ",0,1);
                     lcdtextwrite(0,"LINE 2       O  ",2);
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
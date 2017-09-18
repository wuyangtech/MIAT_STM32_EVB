#include "lcd_func.h"

#define init1 0x38
#define init2 0x0E
#define init3 0x06
#define init4 0x80
#define clr   0x01

#define right 0x1C
#define left  0x18
#define hm    0x02

/* Private functions ---------------------------------------------------------*/
void init_lcd(void) /* LCD 8 bit 存取介面初始化 */
{

    //GPIO_ResetBits(GPIOC, en);       /* EN 信號低電位 */
    //write_com(0x38);  /* 8 bit I/O，雙列顯示      */
    //write_com(0x0e);  /* 游標出現，不閃爍         */
    //write_com(0x06);  /* 每次向右移，顯示幕不移動 */
    //write_com(0x01);  /* 清除 LCD 顯示幕          */
    //write_com(0x80);

    delay(100);
    // initiatize lcd after a short pause
    // needed by the LCDs controller
    write_com(init1);  
                         
    delay(64);                      
    write_com(init1);  
                         
    delay(50);                      
    write_com(init1);  
 
    delay(50);                     
 
    write_com(init2);  // display control:
                         // turn display on, cursor on, no blinking
    delay(20);                      
    write_com(init3);  // entry mode set: 06
                         // increment automatically, display shift, right shift
    delay(20);                      
                       
    write_com(clr);  // clear display, set cursor position to zero  
    delay(100);                      
    write_com(init4);
                        
    delay(20);


}




/*----------------------------------*/
void delay(int d) //短暫副程式 
{
   int i, j;
    for(i = 0; i < d; i++)
       for(j = 0; j < 200; j++)  ;
}

/*--------------------*/
void en1(void) /* LCD 致能控制信號 */
{    
      GPIO_SetBits(GPIOC, en); delay(1);
      GPIO_ResetBits(GPIOC,en);
}

void write_com(unsigned char c)/* 寫入指令暫存器 */
{
    //GPIO_Write(GPIOC,c);
    //GPIO_ResetBits(GPIOC,rs);
    //en1();  

    GPIO_Write(GPIOC, c);
    GPIO_ResetBits(GPIOC, rs);
    GPIO_ResetBits(GPIOC, rw);

    
    GPIO_ResetBits(GPIOC, en);        
    delay(1);
    // send a pulse to enable    

    GPIO_SetBits(GPIOC, en);
    delay(1);
    GPIO_ResetBits(GPIOC, en);  
    delay(1);
    delay(10);  

}

/*-----------------------------*/
void write_data(unsigned char c)/* 寫入資料暫存器 */
{
    //GPIO_Write(GPIOC,c);
    //GPIO_SetBits(GPIOC,rs);
    //en1();


    GPIO_Write(GPIOC, c);    
    GPIO_SetBits(GPIOC, rs);
    GPIO_ResetBits(GPIOC, rw);   
    
    GPIO_ResetBits(GPIOC, en);       
    delay(1);
    // send a pulse to enable 


    GPIO_ResetBits(GPIOC, en);        
    delay(1);
    // send a pulse to enable    

    GPIO_SetBits(GPIOC, en);
    delay(1);
    GPIO_ResetBits(GPIOC, en);  
    delay(1);

}



/*在 LCD 的第一行或第二行印出字元 */
void print(char line, char *str)
{	   
    unsigned char i ;
    if(line == 1) /* 先將某行清為空白 */
    {
        write_com(0x80); /* 設定 LCD 的第一行位址 */
        for(i = 0; i < 16; i++) write_data(' ');
        write_com(0x80);
    }
    else
    {
        write_com(0xc0);/* 設定 LCD 的第二行位址 */
        for(i = 0; i < 16; i++) write_data(' ');
        write_com(0xc0);
   }
   /* 寫入字元資料 */
    do{ write_data(*str++); }
    while(*str!='\0');
}


  /*---------------*/
void prline1(char x, char w) /* 在 LCD第一行特定位置顯示字元 */
{
    write_com(0x80 + x);/* 設定 LCD 的第一行某一位址 */
    write_data(w);    /* 寫入資料 */
}

  /*--------------------*/
void prline2(char x, char w) /* 在 LCD第二行特定位置顯示字元 */
{
    write_com(0xc0 + x);/* 設定 LCD 的第二行某一位址 */
    write_data(w);      /* 寫入資料 */
}



void clear(void)
{
    write_com(clr); //clear screen 
}


void home(void)
{
    write_com(hm);  // set cursor position to zero
}

void setCursor(char index)
{
    char cmd;
    if(index < 16) cmd = 0x80 + index;
    else           cmd = 0xc0 + index - 16;
    
    write_com(cmd);
}

void shiftDisplayLeft(void)
{ 
    write_com(left);
}

void shiftDisplayRight(void)
{
    write_com(right);
}




/*-------------------------*/
void pf4h(unsigned int value)
{
    char buf[5];

    buf[0] = tohex((value&0xf000)>>12);
    buf[1] = tohex((value&0x0f00)>>8);
    buf[2] = tohex((value&0x00f0)>>4);
    buf[3] = tohex(value&0x000f);
    buf[4] = 0;

    print(1, buf);
}

/*-------------------------*/
char tohex(unsigned char value)
{
    if(value > 9)
    {
        switch(value)
        {
	        case 10: return('a');
            case 11: return('b');
            case 12: return('c');
            case 13: return('d');
            case 14: return('e');
            case 15: return('f');
            default: return('X');
        }
    }
    else
    {
        return(value + 0x30);
    }
}


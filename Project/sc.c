#include <REGX51.H>
unsigned char SO[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
sbit RED1 = P2 ^ 0;
sbit YELLOW1 = P2 ^ 1;
sbit GREEN1 = P2 ^ 2;
sbit RED2 = P2 ^ 5;
sbit YELLOW2 = P2 ^ 4;
sbit GREEN2 = P2 ^ 3;
sbit COL1 = P1 ^ 0;
sbit COL2 = P1 ^ 1;
sbit COL3 = P1 ^ 2;
sbit ROW1 = P1 ^ 3;
sbit ROW2 = P1 ^ 4;
sbit ROW3 = P1 ^ 5;
sbit ROW4 = P1 ^ 6;
int index = 0;
int count_red, count_green, count_yellow;
int count_red1, count_green1, count_yellow1;
int count_red2, count_green2, count_yellow2;
int i;
unsigned char key[9] = {-1, -1, -1, -1, -1, -1,-1,-1};//Chua gia tri nhap vao den giao thong
//////////////////////////////////////////////////////
void delay(int time)
{
    while (time--);
}
void hienthi(int number, int number2)
{
    for (i = 0; i < 30; i++)
    {
        P3_4 = 1;
        P0 = SO[number / 10];
        delay(1000);
        P3_4 = 0;
        P3_5 = 1;
        P0 = SO[number % 10];
        delay(1000);
        P3_5 = 0;
        P3_6 = 1;
        P0 = SO[number2 / 10];
        delay(1000);
        P3_6 = 0;
        P3_7 = 1;
        P0 = SO[number2 % 10];
        delay(1000);
        P3_7 = 0;
    }
}
void start()
{
    count_red1 = count_red;
    count_green1 = count_green;
    count_red2 = count_green + count_yellow + 1;
    count_green2 = count_red - count_yellow - 1;
    count_yellow1 = count_yellow2 = count_yellow;
    for (count_red2; count_red2 >= 0; count_red2--)
    {
        if (count_green1 >= 0)
        {
            RED1 = 0;
            YELLOW1 = 0;
            GREEN1 = 1;
            RED2 = 1;
            YELLOW2 = 0;
            GREEN2 = 0;
            hienthi(count_green1, count_red2);
						count_green1--;
        }
        else
        {
						
            RED1 = 0;
            YELLOW1 = 1;
            GREEN1 = 0;
            RED2 = 1;
            YELLOW2 = 0;
            GREEN2 = 0;
            hienthi(count_yellow1, count_red2); 
						count_yellow1--;
         }
    }
    for (count_red1; count_red1 >= 0; count_red1--)
    {
        if (count_green2 >= 0)
        {
            RED1 = 1;
            YELLOW1 = 0;
            GREEN1 = 0;
            RED2 = 0;
            YELLOW2 = 0;
            GREEN2 = 1;
            hienthi(count_red1, count_green2);
						count_green2--;
        }
        else
        {
            RED1 = 1;
            YELLOW1 = 0;
            GREEN1 = 0;
            RED2 = 0;
            YELLOW2 = 1;
            GREEN2 = 0;
            hienthi(count_red1, count_yellow2);
            count_yellow2--;
        }
    }
}
void keyPress()
{
    COL1 = 0;
    if (ROW1 == 0)
    {
        key[index++] = 1;
        delay(50000);
    }
    if (ROW2 == 0)
    {
        key[index++] = 4;
        delay(50000);
    }
    if (ROW3 == 0)
    {
        key[index++] = 7;
        delay(50000);
    }
    if (ROW4 == 0)
		{
				key[index++] = -2;
        delay(50000);
		}
    COL1 = 1;
    COL2 = 0;
    if (ROW1 == 0)
    {
        key[index++] = 2;
        delay(50000);
    }
    if (ROW2 == 0)
    {
        key[index++] = 5;
        delay(50000);
    }
    if (ROW3 == 0)
    {
        key[index++] = 8;
        delay(50000);
    }
    if (ROW4 == 0)
    {
        key[index++] = 0;
        delay(50000);
    }
    COL2 = 1;
    COL3 = 0;
    if (ROW1 == 0)
    {
        key[index++] = 3;
        delay(50000);
    }
    if (ROW2 == 0)
    {
        key[index++] = 6;
        delay(50000);
    }
    if (ROW3 == 0)
    {
        key[index++] = 9;
        delay(50000);
    }
    if (ROW4 == 0)
        delay(50000);
    COL3 = 1;
}
void initTime()
{
    index = 0;
    while (index < 9)
    {
        keyPress();
				if(key[0]!=-2)
				{
					index = 0;
					continue;
				}
        if (index < 3 && key[0] == -2)
        {
            GREEN1 = 1;
            RED1 = 0;
            YELLOW1 = 0;
        }
        if (index >= 3 && index < 6 && key[3] == -2)
        {
            GREEN1 = 0;
            RED1 = 0;
            YELLOW1 = 1;
        }
        if (index >= 6 && index < 9 && key[6] == -2)
        {
            GREEN1 = 0;
            RED1 = 1;
            YELLOW1 = 0;
        }
    }
}
////////////////////////////////////////////////////////////////
////// Chuong trinh chinh///////////////////////////////////////
void main()
{
    P2 = 0x00;
    EA = 1;
    EX0 = 1; // Ngat ngoai 0
    initTime();
    count_green = key[1] * 10 + key[2];
    count_yellow = key[4] * 10 + key[5];
    count_red = key[7] * 10 + key[8];
    while (1)
        start();
}
////////////////////////////////////////////////////////////////
//////////////Ngat ngoai 0 /////////////////////////////////////
void ngat() interrupt 0
{
    count_red = 10;
    count_green = 20;
    count_yellow = 3;
    while (1)
        start();
}

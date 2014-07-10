/********************************************************************
* 文件名  ： 点阵显示.c
* 描述    :  按下相应的独立按键，会在数码管上显示相应的左右中
             按S19显示左
			 按S18显示中
			 按S17显示右
***********************************************************************/
#include <reg52.H>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char

sbit KEY1 = P3^2;    
sbit KEY2 = P3^3;
sbit KEY3 = P3^4;

unsigned char code tabP2[]={0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
//中 的编
unsigned char code tabP0ZHONG[]={0x00,0x3C,0x24,0x24,0xFF,0x24,0x24,0x3C};
//“左”的
unsigned char code tabP0Z[]={0x00,0x94,0x94,0xF4,0x9F,0x94,0x24,0x44};
//“右”的
unsigned char code tabP0Y[]={0x00,0xF4,0x94,0x94,0x9F,0xF4,0x24,0x44};


/********************************************************************
* 名称 : Delay_1ms()
* 功能 : 延时子程序，延时时间为 1ms * x
* 输入 : x (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void Delay_1ms(uchar i)//1ms延时
{
	uchar x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}
/********************************************************************
* 名称 : Delay()
* 功能 : 实现按键功能，并在LED上显示
* 输入 : 无
* 输出 : 无
***********************************************************************/
uchar KEY(void)
{
	if(KEY1==0 || KEY2==0 || KEY3==0)	
	{
		Delay_1ms(20);   		//20毫秒软件防抖
		if(KEY1 == 0)
		{ 
			Delay_1ms(100);			//延时0.1秒再进行下次按键的检测
			return 1; 
		}
		if(KEY2 == 0)
		{			
			Delay_1ms(100);			//延时0.1秒再进行下次按键的检测
			return 2;
		}
		if(KEY3 == 0)
		{			
			Delay_1ms(100);			//延时0.1秒再进行下次按键的检测
			return 3;  
		}
		return 0;
	}
	return 0;	
}
/********************************************************************
* 名称 : Main()
* 功能 : 主函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void main()
{
	int i,temp,flag;
	while(1)
	{
		temp = KEY();
		if(temp != 0)				   //这里判断是否按键按下，按下后，才改变要显示的值
		{
			flag = temp;			   //存标志
		}
		for(i=0;i<8;i++)
		{
			P0=0;
			P2=tabP2[i];
			if(flag == 1)
			{  	
				P0=tabP0Z[i];		   //显示“左”
			}
			if(flag == 2)
			{
				P0=tabP0ZHONG[i];	   //显示 中
			}
			if(flag == 3)
			{
				P0=tabP0Y[i];		   //显示“右”
			}
			Delay_1ms(2);
		}		
	}
}
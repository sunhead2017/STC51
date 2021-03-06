/********************************************************************
* 文件名  ： 串口接收试验.c
* 描述    :  该文件实现通过单片机从电脑接收数据(数据位数字）。通过数码管显示
			 该试验使用的晶振是11.0592,如果使用12M晶振，会出现串口接收
			 不正常的情况。原因是用12M晶振，波特率9600时的误差率达 8%
			 当下载这个程序到单片机时，单片机的最高为为乱码，是正常现象，
			 按一下复位键便可。是由于单片机下载也是通过串口下载引起的。

***********************************************************************/
#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint  unsigned int 

uchar code table[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar LED_Buffer[8] = {0};      //从串口接收的数据

/********************************************************************
* 名称 : Delay_1ms()
* 功能 : 延时子程序，延时时间为 1ms * x
* 输入 : x (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void Delay_1ms(uint i)//1ms延时
{
	uchar x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}

/********************************************************************
* 名称 : Com_Int()
* 功能 : 串口中断子函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Com_Int(void) interrupt 4
{
	static uchar i = 7;    //定义为静态变量，当重新进入这个子函数时 i 的值不会发生改变
	EA = 0;
	if(RI == 1)   //当硬件接收到一个数据时，RI会置位
	{
		LED_Buffer[i] = SBUF - 48; //这里减去48是因为从电脑中发送过来的数据是ASCII码。
		RI = 0;  
		if(i==0) i = 8;  
		i--;		
	}
	EA = 1;
}

/********************************************************************
* 名称 : Com_Init()
* 功能 : 串口初始化，晶振11.0592,波特率9600，使能了串口中断
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Com_Init(void)
{
     TMOD = 0x20;
     PCON = 0x00;
     SCON = 0x50;			
     TH1 = 0xFd;    //设置波特率 9600
     TL1 = 0xFd;
     TR1 = 1;		//启动定时器1
	 ES = 1;		//开串口中断
	 EA = 1;		//开总中断		
}

/********************************************************************
* 名称 : Main()
* 功能 : 主函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Main()
{
	uchar i = 0;
	Delay_1ms(100);
	Com_Init();
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P0 = table[LED_Buffer[i]];
			P2 = i;
			Delay_1ms(1);
		}
	}
}						   

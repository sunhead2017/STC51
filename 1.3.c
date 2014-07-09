/********************************************************************* 
描述: 该程序是一个最简单的单片机代码。实现了一个LED的不停闪烁。
		  每个0.2秒，两灭交替一次。		 
***********************************************************************/
#include<reg52.h>
#define uchar unsigned char   //这里用"uchar"代替"unsigned char"，"uchar"用来定义无符号字符型数。
#define uint  unsigned int	  //"uint"用来定义无符号整型数。
sbit Show_LED = P0^0;		  //用来声明P1.0口为程序所要控制的端口,"sbit"是KEIL专门用来声明某位IO口

/********************************************************************
* 名称 : Delay()
* 功能 : 延时,延时时间为 10ms * del。这是通过软件延时，有一定误差。
* 输入 : del
* 输出 : 无
***********************************************************************/
void Delay(uint del)
{
	uint i,j;
	for(i=0; i<del; i++)
	for(j=0; j<1827; j++)     //这个是通过软件仿真得出的数  
	;
}

/********************************************************************
* 名称 : Main()
* 功能 : 实现灯的闪烁
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Main(void)
{
	while(1)
	{
		Show_LED = 1;
		Delay(20);		//Delay(del)中的数为延时的时间参数，延时时间为 10ms * del.
		Show_LED = 0;
		Delay(20);
	}
}

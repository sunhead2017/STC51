/********************************************************************
* 描述:	点亮P1口的一个LED灯
       	该程序是单片机学习中最简单最基础的，
 	通过程序了解如何控制端口的高低电平	 
***********************************************************************/

#include<reg52.h>
#define uchar unsigned char   	//这里用"uchar"代替"unsigned char"，"uchar"用来定义无符号字符型数。
#define uint  unsigned int	//"uint"用来定义无符号整型数。			

/********************************************************************
* 名称 : Main()
* 功能 : 点亮最后一个LED
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Main(void)
{
	P0 = 0xfe;				//点亮最后一个LED
	while(1)
	{
	}
}
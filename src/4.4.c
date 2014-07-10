/********************************************************************
* 文件名  ： 数码管字符显示.c
* 描述    :  按下S19按键，数码管上显示的数字加1。

***********************************************************************/
#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int
sbit KEY = P3^2;
/********************************************************************
* 名称 : Main()
* 功能 : 数码管的显示
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Main(void)
{
	uchar i = 0;
	P2 = 0xfe;
	while(1)
	{
		if(KEY == 1)
		{
			P0 = 0x76;  //"H";		 
		}
		if(KEY == 0)
		{
			P0 = 0x38;  //"L"	
		}
	}
}

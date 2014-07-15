/********************************************************************
* 描述    :  继电器实验，按S19继电器吸合，按S18继电器释放。		 
* 杜邦线接法：P1.2用杜邦线连接到J17的左边第二个。
***********************************************************************/
#include <reg52.h>
#define uchar unsigned char
#define uint  unsigned int
 
sbit key1=P3^2;//定义按键位置，按了P3.2后继电器吸合
sbit key2=P3^3;//定义按键位置，按了P3.3后继电器释放
sbit RELAY = P1^1;

/********************************************************************
* 名称 : Delay_1ms()
* 功能 : 延时子程序，延时时间为 1ms * x
* 输入 : x (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void Delay(uint i)
{
	uchar x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}

main()
{
	while(1)
	{ 
		if(!key1)     //按下相应的按键
        {
			Delay(15);
        	if(!key1)     //去抖后是否按下相应的按键
		    {
		   		RELAY=1; //继电器吸合
		  	}
		}
		if(!key2)     //按下相应的按键
        {
			Delay(15);
        	if(!key2)     //去抖后是否按下相应的按键
		  	{
		   		RELAY=0; //继电器释放
		  	}
		}
    }
}

/********************************************************************
* 文件名  :  蜂鸣器发声.c
* 描述    :  蜂鸣器通过交替变化的电平后，会发出蜂鸣声。			 
* 杜邦线接法：P1.2用杜邦线连接到J17的左边第二个。
***********************************************************************/
#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int
uchar Count;

sbit Speak =P1^2;				  //蜂鸣器器控制脚 　
/*以下数组是音符编码*/
unsigned char code SONG[] ={      //祝你平安
0x26,0x20,0x20,0x20,0x20,0x20,0x26,0x10,0x20,0x10,0x20,0x80,0x26,0x20,0x30,0x20,
0x30,0x20,0x39,0x10,0x30,0x10,0x30,0x80,0x26,0x20,0x20,0x20,0x20,0x20,0x1c,0x20,
0x20,0x80,0x2b,0x20,0x26,0x20,0x20,0x20,0x2b,0x10,0x26,0x10,0x2b,0x80,0x26,0x20,
0x30,0x20,0x30,0x20,0x39,0x10,0x26,0x10,0x26,0x60,0x40,0x10,0x39,0x10,0x26,0x20,
0x30,0x20,0x30,0x20,0x39,0x10,0x26,0x10,0x26,0x80,0x26,0x20,0x2b,0x10,0x2b,0x10,
0x2b,0x20,0x30,0x10,0x39,0x10,0x26,0x10,0x2b,0x10,0x2b,0x20,0x2b,0x40,0x40,0x20,
0x20,0x10,0x20,0x10,0x2b,0x10,0x26,0x30,0x30,0x80,0x18,0x20,0x18,0x20,0x26,0x20,
0x20,0x20,0x20,0x40,0x26,0x20,0x2b,0x20,0x30,0x20,0x30,0x20,0x1c,0x20,0x20,0x20,
0x20,0x80,0x1c,0x20,0x1c,0x20,0x1c,0x20,0x30,0x20,0x30,0x60,0x39,0x10,0x30,0x10,
0x20,0x20,0x2b,0x10,0x26,0x10,0x2b,0x10,0x26,0x10,0x26,0x10,0x2b,0x10,0x2b,0x80,
0x18,0x20,0x18,0x20,0x26,0x20,0x20,0x20,0x20,0x60,0x26,0x10,0x2b,0x20,0x30,0x20,
0x30,0x20,0x1c,0x20,0x20,0x20,0x20,0x80,0x26,0x20,0x30,0x10,0x30,0x10,0x30,0x20,
0x39,0x20,0x26,0x10,0x2b,0x10,0x2b,0x20,0x2b,0x40,0x40,0x10,0x40,0x10,0x20,0x10,
0x20,0x10,0x2b,0x10,0x26,0x30,0x30,0x80,0x00,
                                  //路边的野华不要采
0x30,0x1C,0x10,0x20,0x40,0x1C,0x10,0x18,0x10,0x20,0x10,0x1C,0x10,0x18,0x40,0x1C,
0x20,0x20,0x20,0x1C,0x20,0x18,0x20,0x20,0x80,0xFF,0x20,0x30,0x1C,0x10,0x18,0x20,
0x15,0x20,0x1C,0x20,0x20,0x20,0x26,0x40,0x20,0x20,0x2B,0x20,0x26,0x20,0x20,0x20,
0x30,0x80,0xFF,0x20,0x20,0x1C,0x10,0x18,0x10,0x20,0x20,0x26,0x20,0x2B,0x20,0x30,
0x20,0x2B,0x40,0x20,0x20,0x1C,0x10,0x18,0x10,0x20,0x20,0x26,0x20,0x2B,0x20,0x30,
0x20,0x2B,0x40,0x20,0x30,0x1C,0x10,0x18,0x20,0x15,0x20,0x1C,0x20,0x20,0x20,0x26,
0x40,0x20,0x20,0x2B,0x20,0x26,0x20,0x20,0x20,0x30,0x80,0x20,0x30,0x1C,0x10,0x20,
0x10,0x1C,0x10,0x20,0x20,0x26,0x20,0x2B,0x20,0x30,0x20,0x2B,0x40,0x20,0x15,0x1F,
0x05,0x20,0x10,0x1C,0x10,0x20,0x20,0x26,0x20,0x2B,0x20,0x30,0x20,0x2B,0x40,0x20,
0x30,0x1C,0x10,0x18,0x20,0x15,0x20,0x1C,0x20,0x20,0x20,0x26,0x40,0x20,0x20,0x2B,
0x20,0x26,0x20,0x20,0x20,0x30,0x30,0x20,0x30,0x1C,0x10,0x18,0x40,0x1C,0x20,0x20,
0x20,0x26,0x40,0x13,0x60,0x18,0x20,0x15,0x40,0x13,0x40,0x18,0x80,0x00,

};

/********************************************************************
* 名称 : Time0_Init()
* 功能 : 定时器的初始化，定时时间可用光碟中软件计算，11.0592MZ晶振，10ms
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Time0_Init()
{
	TMOD = 0x01;
	IE 	 = 0x82;
	TH0  = 0xDC;
	TL0  = 0x00;		
}

/********************************************************************
* 名称 : Time0_Int()
* 功能 : 定时器中断，中断中实现 Count 加一
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Time0_Int() interrupt 1
{
	TH0 = 0xDC;
	TL0 = 0x00;
	Count++;			//长度加1
}

/********************************************************************
* 名称 : Delay_xMs()
* 功能 : 延时子程序，经过软件调试，测得延时程序大概为55us.
* 输入 : x 
* 输出 : 无
***********************************************************************/
void Delay_xMs(uint x)
{
    uint i,j;
    for(i=0; i<x; i++)
    {
        for(j=0; j<3; j++);
    }
}

/********************************************************************
* 名称 : Play_Song()
* 功能 : 播放蜂鸣器控制程序
* 输入 : i (选择播放哪首歌曲，0为“祝你平安”，1为“路边的野花你不要采”
* 输出 : 无
***********************************************************************/
void Play_Song(uchar i)
{
	uchar Temp1,Temp2;
	uint Addr;
	Count = 0;						//中断计数器清0
	Addr = i * 217;
	while(1)
	{
		Temp1 = SONG[Addr++];
	    if (Temp1 == 0xFF)          //休止符
	    {
	    	TR0 = 0;
	    	Delay_xMs(100);
	    }
	    else if (Temp1 == 0x00)	  //歌曲结束符
	    {
	    	return;
	    }
	    else
	    {
	    	Temp2 = SONG[Addr++];
	    	TR0 = 1;
	  		while(1)
	  		{
	    		Speak = ~Speak;
	    		Delay_xMs(Temp1);
	    		if(Temp2 == Count)
	    		{
	    			Count = 0;
	    			break;
	    		}
	    	}
	    }
	}
}
/********************************************************************
* 名称 : Main()
* 功能 : 主函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Main()
{
	Time0_Init();			//定时器0中断初始化
	while(1)
	{
		Play_Song(0);		//Play_Song(0)为祝你平安    Play_Song(1)为路边的野花你不要裁
	}
}
   
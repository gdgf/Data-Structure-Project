
#include <stdio.h>
#include <stdlib.h>         //malloc
#include <time.h>             //获取系统时间所用函数
#include <conio.h>            //getch()
#include <windows.h>          //设置光标信息 mallco

#define MaxSize 5          /*定义停车场栈长度*/
#define PRICE 0.05         /*每车每分钟收费值*/
#define BASEPRICE 0.5      //基础停车费
#define Esc 27             //退出系统
#define Exit 3				//结束对话
#define Stop 1				//停车
#define Drive 2				//取车
int jx=0,jy=32;               //全局变量日志打印位置
typedef struct
{int hour;
 int minute;
}Time,*PTime;                     /*时间结点*/

typedef struct             /*定义栈元素的类型即车辆信息结点*/
{int num ;                 /*车牌号*/
 Time arrtime;             /*到达时刻或离区时刻*/
}CarNode;

typedef struct             /*定义栈,模拟停车场*/
{CarNode stack[MaxSize];
 int top;
}SqStackCar;

typedef struct node        /*定义队列结点的类型*/
{int num;                  /*车牌号*/
 struct node *next;
}QueueNode;

typedef struct                              /*定义队列,模拟便道*/
{QueueNode *front,*rear;
}LinkQueueCar;
#include"Parking_L.h"
void main(void)
{
	int i,a;
	char c;
	SqStackCar s1,s2;                            //停车栈和暂存栈
	LinkQueueCar p;                              //队列
	InitSeqStack(&s1);
	InitSeqStack(&s2);
	InitLinkQueue(&p);
	printf("                                 停车场管理系统\n\n");
	printf("*************************         欢迎光临        ***************************\n");
	printf("      收费标准：基础费0.5元，每分钟收取0.05元，收费精确到0.1元\n");
	printf("      PS:车牌号由阿拉伯数字组成");
	panitPL();
	printcar();		gotoxy(0,-3);
	c=0;               //接受按键
	while(1)          //按ESC退出系统
	{
		for(i=2;i>-1 ;i--)                           //初始化对话框
			qingping(i);
		printf("按ESC退出系统,其它键开始对话");
		c=getch();
		if(c==Esc)
		{
			qingping(0);
			break;
		}

		while(1)
		{
			qingping(2);
			gotoxy(28,8);	printf("欢迎来到停车场！我是管理员小张。");
			gotoxy(28,9);	printf("请您按↑↓选择需要的服务        ");
			gotoxy(28,11);	printf("   1.我要停车");
			gotoxy(28,12);	printf("   2.我要取车");
			gotoxy(28,13);	printf("   3.结束对话");                       //打印对话框完成
			a=getkey();
			if(a==Exit)
			{
				printf("结束服务。");
				break;
			}
			switch(a)
			{
			case Stop:                                  //停车
				Arrive(&s1,&p,getcarInfo() );
				break;
			case Drive:									//取车
				Leave(&s1,&s2,&p,getcarInfo() );
				break;
			}
		}


	}
}

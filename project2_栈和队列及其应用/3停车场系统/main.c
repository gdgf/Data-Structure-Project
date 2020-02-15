#include"Parking_L.h"
#include <stdio.h>
#include <conio.h>            //getch()

#define MaxSize 5             //定义停车场栈长度
#define Esc 27                //退出系统
#define Exit 3				  //结束对话
#define Stop 1				  //停车
#define Drive 2				  //取车
//时间结点
struct Time{
    int hour;
    int minute;
};
//定义栈元素的类型即车辆信息结点
struct CarNode{
    int num ;                 //车牌号
    Time arrtime;             //到达时刻或离区时刻
};
//定义顺序栈,模拟停车场
struct SqStackCar{
    CarNode stack[MaxSize];
    int top;
};

//定义链队列结点的类型
typedef struct node{
    int num;                  //车牌号
    struct node *next;
}QueueNode;
//定义队列,模拟便道
struct LinkQueueCar{
    QueueNode *front,*rear;
};
int  main(void)
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
	panitPL();          //画出系统界面
	printcar();         //打印停车场界面
	gotoxy(0,-3);
	c=0;                //接受按键
	while(1){            //按ESC退出系统
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
			if(a==Exit){
				printf("结束服务。");
				break;
			}
			switch(a){
                case Stop:                                  //停车
                    Arrive(&s1,&p,getcarInfo());
                    break;
                case Drive:									//取车
                    Leave(&s1,&s2,&p,getcarInfo());
                    break;
			}//switch
		}//while
	}//while
	return 1;
}

#ifndef PARKING_L_H_INCLUDED
#define PARKING_L_H_INCLUDED

struct Time;
typedef struct Time Time;
typedef struct Time* PTime;
struct CarNode;
typedef struct CarNode CarNode;
struct SqStackCar;
typedef struct SqStackCar SqStackCar;
struct LinkQueueCar;
typedef struct LinkQueueCar LinkQueueCar;

void InitSeqStack(SqStackCar *s);
/*初始化栈*/
int push(SqStackCar *s,CarNode x);
/* push入栈函数 */
CarNode pop(SqStackCar *s);
/*栈顶元素出栈*/
void InitLinkQueue(LinkQueueCar *q);
/*初始化队列*/
void EnLinkQueue(LinkQueueCar *q,int x);
/*数据入队列*/
int DeLinkQueue(LinkQueueCar *q);
/*数据出队列*/
void Arrive(SqStackCar *stop,LinkQueueCar *lq,CarNode x);
/*对传入的车辆进行入栈 栈满则入队列*/
void Leave(SqStackCar *s1,SqStackCar *s2,LinkQueueCar *p,CarNode x);
/*查找栈中s1的x并出栈，栈中没有则查找队p中并出队，打印离开收费信息*/
PTime get_time();
/*获取系统时间*/
void gotoxy(int x,int y);
/*移动光标*/
void panitPL();
/*画出系统界面*/

void qingping(int a);
/*更新对话框前将原对话晴空*/
int getkey();
/*用上下键移动选择*/
CarNode getcarInfo();
/*输入车辆信息*/

void printcar();
/*打印停车场*/
void printlog(Time t,int n,int io,char ab,int po,double f);
/*车进入打印日志*/
void printstop(int a,int num,int x0,int y0);
/*停车*/
void printleave(int a,int po,int num);
/*取车*/
#endif // PARKING_L_H_INCLUDED

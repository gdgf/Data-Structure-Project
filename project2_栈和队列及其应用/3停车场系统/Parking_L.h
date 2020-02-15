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
/*��ʼ��ջ*/
int push(SqStackCar *s,CarNode x);
/* push��ջ���� */
CarNode pop(SqStackCar *s);
/*ջ��Ԫ�س�ջ*/
void InitLinkQueue(LinkQueueCar *q);
/*��ʼ������*/
void EnLinkQueue(LinkQueueCar *q,int x);
/*���������*/
int DeLinkQueue(LinkQueueCar *q);
/*���ݳ�����*/
void Arrive(SqStackCar *stop,LinkQueueCar *lq,CarNode x);
/*�Դ���ĳ���������ջ ջ���������*/
void Leave(SqStackCar *s1,SqStackCar *s2,LinkQueueCar *p,CarNode x);
/*����ջ��s1��x����ջ��ջ��û������Ҷ�p�в����ӣ���ӡ�뿪�շ���Ϣ*/
PTime get_time();
/*��ȡϵͳʱ��*/
void gotoxy(int x,int y);
/*�ƶ����*/
void panitPL();
/*����ϵͳ����*/

void qingping(int a);
/*���¶Ի���ǰ��ԭ�Ի����*/
int getkey();
/*�����¼��ƶ�ѡ��*/
CarNode getcarInfo();
/*���복����Ϣ*/

void printcar();
/*��ӡͣ����*/
void printlog(Time t,int n,int io,char ab,int po,double f);
/*�������ӡ��־*/
void printstop(int a,int num,int x0,int y0);
/*ͣ��*/
void printleave(int a,int po,int num);
/*ȡ��*/
#endif // PARKING_L_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>         //malloc
#include <time.h>             //��ȡϵͳʱ�����ú���
#include <conio.h>            //getch()
#include <windows.h>          //���ù����Ϣ mallco

#define MaxSize 5          /*����ͣ����ջ����*/
#define PRICE 0.05         /*ÿ��ÿ�����շ�ֵ*/
#define BASEPRICE 0.5      //����ͣ����
#define Esc 27             //�˳�ϵͳ
#define Exit 3				//�����Ի�
#define Stop 1				//ͣ��
#define Drive 2				//ȡ��
int jx=0,jy=32;               //ȫ�ֱ�����־��ӡλ��
typedef struct
{int hour;
 int minute;
}Time,*PTime;                     /*ʱ����*/

typedef struct             /*����ջԪ�ص����ͼ�������Ϣ���*/
{int num ;                 /*���ƺ�*/
 Time arrtime;             /*����ʱ�̻�����ʱ��*/
}CarNode;

typedef struct             /*����ջ,ģ��ͣ����*/
{CarNode stack[MaxSize];
 int top;
}SqStackCar;

typedef struct node        /*������н�������*/
{int num;                  /*���ƺ�*/
 struct node *next;
}QueueNode;

typedef struct                              /*�������,ģ����*/
{QueueNode *front,*rear;
}LinkQueueCar;
#include"Parking_L.h"
void main(void)
{
	int i,a;
	char c;
	SqStackCar s1,s2;                            //ͣ��ջ���ݴ�ջ
	LinkQueueCar p;                              //����
	InitSeqStack(&s1);
	InitSeqStack(&s2);
	InitLinkQueue(&p);
	printf("                                 ͣ��������ϵͳ\n\n");
	printf("*************************         ��ӭ����        ***************************\n");
	printf("      �շѱ�׼��������0.5Ԫ��ÿ������ȡ0.05Ԫ���շѾ�ȷ��0.1Ԫ\n");
	printf("      PS:���ƺ��ɰ������������");
	panitPL();
	printcar();		gotoxy(0,-3);
	c=0;               //���ܰ���
	while(1)          //��ESC�˳�ϵͳ
	{
		for(i=2;i>-1 ;i--)                           //��ʼ���Ի���
			qingping(i);
		printf("��ESC�˳�ϵͳ,��������ʼ�Ի�");
		c=getch();
		if(c==Esc)
		{
			qingping(0);
			break;
		}

		while(1)
		{
			qingping(2);
			gotoxy(28,8);	printf("��ӭ����ͣ���������ǹ���ԱС�š�");
			gotoxy(28,9);	printf("����������ѡ����Ҫ�ķ���        ");
			gotoxy(28,11);	printf("   1.��Ҫͣ��");
			gotoxy(28,12);	printf("   2.��Ҫȡ��");
			gotoxy(28,13);	printf("   3.�����Ի�");                       //��ӡ�Ի������
			a=getkey();
			if(a==Exit)
			{
				printf("��������");
				break;
			}
			switch(a)
			{
			case Stop:                                  //ͣ��
				Arrive(&s1,&p,getcarInfo() );
				break;
			case Drive:									//ȡ��
				Leave(&s1,&s2,&p,getcarInfo() );
				break;
			}
		}


	}
}

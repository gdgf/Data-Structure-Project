#include"Parking_L.h"
#include <stdio.h>
#include <conio.h>            //getch()

#define MaxSize 5             //����ͣ����ջ����
#define Esc 27                //�˳�ϵͳ
#define Exit 3				  //�����Ի�
#define Stop 1				  //ͣ��
#define Drive 2				  //ȡ��
//ʱ����
struct Time{
    int hour;
    int minute;
};
//����ջԪ�ص����ͼ�������Ϣ���
struct CarNode{
    int num ;                 //���ƺ�
    Time arrtime;             //����ʱ�̻�����ʱ��
};
//����˳��ջ,ģ��ͣ����
struct SqStackCar{
    CarNode stack[MaxSize];
    int top;
};

//���������н�������
typedef struct node{
    int num;                  //���ƺ�
    struct node *next;
}QueueNode;
//�������,ģ����
struct LinkQueueCar{
    QueueNode *front,*rear;
};
int  main(void)
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
	panitPL();          //����ϵͳ����
	printcar();         //��ӡͣ��������
	gotoxy(0,-3);
	c=0;                //���ܰ���
	while(1){            //��ESC�˳�ϵͳ
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
			if(a==Exit){
				printf("��������");
				break;
			}
			switch(a){
                case Stop:                                  //ͣ��
                    Arrive(&s1,&p,getcarInfo());
                    break;
                case Drive:									//ȡ��
                    Leave(&s1,&s2,&p,getcarInfo());
                    break;
			}//switch
		}//while
	}//while
	return 1;
}

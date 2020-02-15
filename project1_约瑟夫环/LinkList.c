#include"LinkList.h"
#include<stdio.h>
#include<malloc.h>
typedef int DataType;
//�����ṹ��
struct JoseNode{
    DataType Num;
    DataType Passward;
    struct JoseNode *next;
};
typedef struct JoseNode JoseNode;
//��ʼ��ѭ��������
JoseNode* JoseInit()
{
     JoseNode *h=(JoseNode*)malloc(sizeof(JoseNode));
     h->next = h;         //ѭ��������
    return h;
}
//������������
int JoseInsert(JoseNode *h, int pos, DataType num,DataType passward)
{
    JoseNode* p=h,q;
    int i=1;
    if (pos == 1){   //β�巨
        p->Num = num;
        p->Passward=passward;
        p->next = p;
        return 1;
    }
     while(i<pos-1){
         p=p->next;
          i++;
     }
     q=(JoseNode*)malloc(sizeof(JoseNode));
     q->Num=num;
     q->Passward=passward;
     q->next=p->next;
     p->next=q;
     return 1;
  }

//����
void TraverseList(JoseNode* h, int M)
{
     int i = 0;
     JoseNode* p = h;
     printf("������˵ı�ż�����Ϊ��\n");
     while (i<M){
        printf("%d,%d\t", p->Num,p->Passward);
        p = p->next;
        i++;
     }
    printf("\n");
}
void Column(JoseNode *h,int m)
{
    JoseNode* p=h,q;
    DataType e;
	int i;
	while(p->next!=p){
        if(p->Num==1){
            //����m���˳���
            for(i=1;i<m;i++){
                q=p;
                p=p->next;
            }
            //qָ��pָ��Ľ���ǰһ�����
            q->next=p->next;	 //��pָ��Ľ��ɾ����������Ϊm���˳���
            printf("%4d",p->Num);//�����ɾ���Ľ��
            e=p->Passward;
            free(p);
            p=q->next;			 //pָ����һ����㣬���¿�ʼ����
        }
        else{
            //����p->password���˳���
            for(i=1;i<e;i++){
                q=p;
                p=p->next;
            }
            q->next=p->next;	 //��pָ��Ľ��ɾ����������Ϊm���˳���
            printf("%4d",p->Num);//�����ɾ���Ľ��
            e=p->Passward;
            free(p);
            p=q->next;			 //pָ����һ����㣬���¿�ʼ����
        }
    }
    printf("%4d\n",p->Num);
}

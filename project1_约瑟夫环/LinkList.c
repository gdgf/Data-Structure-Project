#include"LinkList.h"
#include<stdio.h>
#include<malloc.h>
typedef int DataType;
//构建结构体
struct JoseNode{
    DataType Num;
    DataType Passward;
    struct JoseNode *next;
};
typedef struct JoseNode JoseNode;
//初始化循环单链表
JoseNode* JoseInit()
{
     JoseNode *h=(JoseNode*)malloc(sizeof(JoseNode));
     h->next = h;         //循环单链表
    return h;
}
//单链表插入操作
int JoseInsert(JoseNode *h, int pos, DataType num,DataType passward)
{
    JoseNode* p=h,q;
    int i=1;
    if (pos == 1){   //尾插法
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

//遍历
void TraverseList(JoseNode* h, int M)
{
     int i = 0;
     JoseNode* p = h;
     printf("参与的人的编号及密码为：\n");
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
            //数到m的人出列
            for(i=1;i<m;i++){
                q=p;
                p=p->next;
            }
            //q指向p指向的结点的前一个结点
            q->next=p->next;	 //将p指向的结点删除，即报数为m的人出列
            printf("%4d",p->Num);//输出被删除的结点
            e=p->Passward;
            free(p);
            p=q->next;			 //p指向下一个结点，重新开始报数
        }
        else{
            //数到p->password的人出列
            for(i=1;i<e;i++){
                q=p;
                p=p->next;
            }
            q->next=p->next;	 //将p指向的结点删除，即报数为m的人出列
            printf("%4d",p->Num);//输出被删除的结点
            e=p->Passward;
            free(p);
            p=q->next;			 //p指向下一个结点，重新开始报数
        }
    }
    printf("%4d\n",p->Num);
}

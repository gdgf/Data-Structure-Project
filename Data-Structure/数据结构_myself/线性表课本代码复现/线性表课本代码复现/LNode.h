#pragma once
/*线性表的单链表存储结构*/

#include"预定义.h"
#include<stdlib.h>
#include<stdio.h>
typedef struct LLNode {
	ElemType data;
	struct  LNode *next;
}LNode,*LinkList;

void CreateList_L(LinkList L, int n);
//手动输入创建

Status CreateList_HL(FILE *fp,LinkList *L, int n);
//头插法创建链表（逆序插入）

Status CreateList_TL(FILE *fp, LinkList *L,int n);
//尾插法建立单链表（顺序插入）

Status ListInit_L(LinkList *L);      
//初始化

Status ClearList_L(LinkList L);
//指控单链表，头节点保留

void DestroyList_L(LinkList *L);
//销毁单链表L,头节点一起销毁

Status ListEmpty_L(LinkList L);
//判断单链表L是否为空

int ListLength_L(LinkList L);
//返回单链表中的元素个数

Status GetElem_L(LinkList L, int i,ElemType *e);   
//得到第i个元素

int LocateElem_L(LinkList L, ElemType e, Status(Compare)(ElemType, ElemType));
//返回单链表L中第一个e与满足compare关系的元素位序

Status PriorElem_L(LinkList L, ElemType cur_e, ElemType *pre_e);
//用pre_e接收cur_ed的前驱

Status NextElem_L(LinkList L, ElemType cur_e, ElemType *next_e);
//用next_e接收cur_ed的前驱

Status ListInsert_L(LinkList L, int i, ElemType e);
//在第i个位置插入元素e

Status ListDelete_L(LinkList L, int i, ElemType *e);
//删除第i个位置的元素

Status ListTraverse_L(LinkList L, void(Visit)(ElemType));
//用Visit函数访问单链表L
 
void ListPrint_L(LinkList L);
//打印
Status Compare(ElemType e1, ElemType e2);
void Visit(ElemType e);
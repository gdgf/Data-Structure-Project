#pragma once
/*
 线性表的动态分配顺序存储结构
*/
#include"预定义.h"

//节点定义
#define LIST_INT_SIZE  100   //初始分配量
#define LISTINCREMENT  10    //每次的增量

typedef struct {
	ElemType *elem;         //基址
	int length;             //当前长度
	int ListSize;           //当前分配的存储容量
}SqList;

Status InitList_Sq(SqList *L);  //初始化
Status ListInsert_Sq(SqList *L, int i, ElemType e);  //在第i的位置插入元素e
Status ListDelete_Sq(SqList *L, int i, ElemType *e);  //删除第i位置的元素，并带回其值
int LocateElem_Sq(SqList L, ElemType e,Status (*compare)(ElemType,ElemType));  //在顺序表中查找第一个与e
void ListTraverse_Sq(SqList L);  //打印
Status compare(ElemType x, ElemType y); //判断是否相等
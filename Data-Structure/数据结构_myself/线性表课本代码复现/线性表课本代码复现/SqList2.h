#pragma once

/*
 * 线性表的实现方式有两种
 ***1.顺序结构
      1.1静态态顺序结构
	  1.2动态顺序结构
 ***2.链式存储结构
 */
//顺序存储结构
//1.1静态顺序结构

#define MaxSize 100
typedef  int ElementType;
typedef struct LNode {
	ElementType Data[MaxSize];
	int Length;
}List1;

//初始化
void InitList1(List1 *L);  
//判断是否为空
int ListEmpty(List1 L);
//按序号查找，若能查找到返回1，否则返回-1。并将第i个数的值赋给e.
int GetElEM1(List1 L, int i, ElementType *e);
//按内容查找
int LocateElem(List1 L, ElementType e);
//在线性表L的第i格位置插入X
int List1Insert(List1 *L, int i, ElementType X);
//删除线性表的第i个元素
int List1Delete(List1 *L, int i,ElementType *e);
//线性表中元素的个数。
int List1Length(List1 L);

void List1print(List1 L);//打印函数



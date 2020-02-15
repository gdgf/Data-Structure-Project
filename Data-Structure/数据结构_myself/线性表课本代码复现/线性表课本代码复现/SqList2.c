#include<stdio.h>
#include"SqList2.h"
//初始化
void InitList1(List1 *L) {
	L->Length= 0;
}
//判断是否为空
int ListEmpty(List1 L) {
	if (L.Length == 0)
		return 1;
	else
		return 0;
}
//按序号查找，若能查找到返回1，否则返回-1。并将第i个数的值赋给e.
int GetElEM1(List1 L, int i, ElementType *e) {
	if (i > L.Length || i <= 0)
		return 0;
	else {
		*e = L.Data[i - 1];
		return 1;
	}
}
//按内容查找
int LocateElem(List1 L, ElementType e) {
	int i;
	for (i = 0; i < L.Length; i++) {
		if (L.Data[i] == e)
			return i + 1;   //数据e在List1中的序号。
	}
	return 0;
}
//在线性表L的第i格位置插入X
int List1Insert(List1 *L, int i, ElementType X) {
	//判断数组是否已满
	if (i > L->Length + 1 || i <= 0) {
		printf("插入的位置不对");
		return 0;
	}
	else if(L->Length>=MaxSize){
		printf("顺序表已满,不能再继续插入\n");
		return 0;
	}
	else {
		int j;
		for (j = L->Length-1; j >= i - 1; j--) 
			L->Data[j + 1] = L->Data[j];   //挪动
		L->Data[i - 1] = X;                //插入
	 	L->Length = L->Length + 1;
		return 1;
	}
}
//删除线性表的第i个元素
int  List1Delete(List1 *L, int i,ElementType*e) {
	int j;
	if (L->Length <= 0) {
		printf("顺序表已空不能删除\n");
		return 0;
	}
	else if (i<1 || i>L->Length) {
		printf("z删除位置不合适\n");
		return 0;
	}
	else {
		*e = L->Data[i - 1];
		for (j = i; j <= L->Length; j++)
			L->Data[j-1] = L->Data[j];
		L->Length = L->Length - 1;
		return 1;
	}
}
//线性表中元素的个数。
int List1Length(List1 L) {
	return L.Length;
}
//打印函数
void List1print(List1 L) {
	int i;
	for (i = 1; i <= L.Length; i++) {
		ElementType e = 0;
		GetElEM1(L, i, &e);
		printf("%d ", e);
	}
	printf("\n");
}
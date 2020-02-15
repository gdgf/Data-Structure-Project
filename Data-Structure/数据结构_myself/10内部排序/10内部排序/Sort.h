#pragma once

#include"预定义.h"
#define MAXSIZE 50

typedef char InfoType[10];
typedef int KeyType;   //定义关键字类型为整数类型
typedef struct {
	KeyType key;               //关键字  
	InfoType otherinfor;       //其他数据项
}RedType;      
//记录类型
typedef struct {
	RedType r[MAXSIZE + 1];    //将r[0]闲置为空，或用作哨兵
	int length;
}Sqlist;

void Init(Sqlist *L); //初始化顺序表
void Insert(Sqlist *L,int i,RedType r);//插入结点
void print(Sqlist L);//打印静态表


//插入排序
void InsertSort(Sqlist *L);    //直接插入排序
void BInsertSort(Sqlist *L);   //折半插入排序


//交换排序
void BubbleSort(Sqlist *L);        //冒泡排序
void QuickSort(Sqlist *L);          //快速排序      
void QSort(Sqlist *L,int low,int high); 
int Partition(Sqlist *L,int low, int high);
#include"Sort.h"
#include<stdio.h>
using namespace std;

#define len 5

int main1() {
	Sqlist SL;
	//初始化
	RedType r[len] = {{2,"ni"},{3,"hao"},{0,"ya"},{10,"4"},{1,"0"} };
	Init(&SL);
	int i;
	for (i = 2; i<=7; i++) {
		Insert(&SL,i,r[i-2]);
	}
	printf("打印数据:\n");
	print(SL);
	
	/*
	printf("进行直接插入排序\n");
	InsertSort(&SL);
	print(SL);
	*/
	/*
	printf("进行折半插入排序\n");
	BInsertSort(&SL);
	*/
	/*
	printf("进行冒泡排序\n");
	BubbleSort(&SL);
	*/
	printf("进行快速排序\n");
	QuickSort(&SL);
	print(SL);
	return 0;
}
#include<stdio.h>
#include"SqList.h"
int main1() {

	int a[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int i;
	printf("测试数据:");
	for (i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");


	printf("SqList测试\n");
	SqList L1;
	
	printf("初始化\n");
	InitList_Sq(&L1);

	printf("插入测试\n");
	for (i = 1; i <= 10; i++)
		ListInsert_Sq(&L1, i, a[i - 1]);
	printf("遍历：");
	ListTraverse_Sq(L1);

	printf("删除：");
	ElemType e3;
	ListDelete_Sq(&L1, 5, &e3);
	printf("删除元素为：%d\n", e3);
	printf("再次遍历：");
	ListTraverse_Sq(L1);

	system("Pause");
	return 0;
}
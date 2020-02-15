#include<stdio.h>
#include<stdlib.h>
#include"LNode.h"
int main3() {
	FILE  *fp;
	LinkList L;
	int i;
	ElemType e;
	
	printf("初始化\n");
	ListInit_L(&L);
	printf("判空：");
	ListEmpty_L(L) ? printf("L为空\n") : printf("L不为空\n");

	printf("插入法构造一个线性链表\n");
    
	for (i = 1; i <= 6; i++) {
		printf("插入元素：%d ",2*i);
		ListInsert_L(L, i, 2 * i);
	}
	printf("\n");

	printf("遍历这个线性表：");
	ListTraverse_L(L, Visit);
	printf("\n");

	printf("线性表的长度为：%d\n", ListLength_L(L));
	
	printf("删除元素:");
	ListDelete_L(L, 4, &e);
	printf("%d\n", e);
	printf("遍历这个线性表：");
	ListTraverse_L(L, Visit);
	printf("\n");

	GetElem_L(L, 2, &e);
	printf("L中的第2个元素为：%d\n", e);

	PriorElem_L(L, 6, &e);
	printf("元素6的前驱为：%d\n", e);

	NextElem_L(L, 6, &e);
	printf("元素6的后继为：%d\n", e);

	printf("对线性表进行销毁：\n");
	printf("销毁L前：");
	L ? printf("L存在\n") : printf("L不存在\n");
	DestroyList_L(&L);
	printf("销毁L后：");
	L ? printf("L存在\n") : printf("L不存在\n");


	//文件输入创建线性表：
	//头插法：
	printf("头插法建立单链表L:");
	fp = fopen("E:\\Programming\\C\\VS\\数据结构\\线性表课本代码复现\\LnodeHL.txt", "r+");
	CreateList_HL(fp, &L, 5);

	fclose(fp);
	ListTraverse_L(L,Visit);
	printf("\n");

	//尾插法
	printf("尾插法建立单链表L:");
	fp = fopen("E:\\Programming\\C\\VS\\数据结构\\线性表课本代码复现\\LnodeTL.txt", "r+");
	CreateList_TL(fp, &L, 5);
	fclose(fp);
	ListTraverse_L(L, Visit);
	printf("\n");
	system("pause");
	return 0;
}

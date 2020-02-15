#include<stdio.h>
#include"Algorithm.h"
int main() {


	//LNode测试
	FILE *fp;
	LinkList la, lb, lc;
	int m=5;
	
	fp = fopen("E:\\Programming\\C\\VS\\数据结构\\线性表课本代码复现\\LnodeHL.txt", "r");
	CreateList_HL(fp, &la, m);
	fclose(fp);
	fp = fopen("E:\\Programming\\C\\VS\\数据结构\\线性表课本代码复现\\LnodeTL.txt", "r");
	CreateList_TL(fp, &lb, m);
	fclose(fp);


	printf("la:");
	ListTraverse_L(la, Visit);
	printf("\n");
	printf("lb:");
	ListTraverse_L(lb, Visit);

	printf("\n");
	MergeList_L(la, &lb, &lc);
	printf("la和lb合并后lc：");
	ListTraverse_L(lc, Visit);
	printf("\n");

	system("pause");
	return 0;
}
#include<stdio.h>
#include"SqList2.h"
int main2() {

	int a[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int i;
	printf("测试数据:");
	for (i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");


	printf("SqList2测试\n");
	List1 L;
	printf("初始化测试\n");
	InitList1(&L);
	
	printf("插入测试:");
	for (i = 1; i <= 10; i++)
		List1Insert(&L, i, a[i - 1]);
	printf("遍历：");
	List1print(L);
	printf("删除测试:");
	ElementType e = 0;
	List1Delete(&L, 2, &e);
	printf("删除的是：%d\n", e);
	printf("再次打印：");
	List1print(L);
	//插入测试
	List1Insert(&L, 5, 100);
	printf("再次打印：");
	List1print(L);

	system("Pause");
	return 0;
}
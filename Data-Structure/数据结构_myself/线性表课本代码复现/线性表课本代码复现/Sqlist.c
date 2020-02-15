#include"SqList.h"
#include<stdlib.h>
Status InitList_Sq(SqList *L) {
	//初始化
	//构造空的线性表
	L->elem = (ElemType*)malloc(LIST_INT_SIZE * sizeof(ElemType));
	if (!L->elem)exit(OVERFLOW);
	L->length = 0;
	L->ListSize = LIST_INT_SIZE;
	return OK;
}
Status ListInsert_Sq(SqList *L, int i, ElemType e) {
	//在第i的位置插入元素e
	ElemType *newbase;
	if (i<1 || i>L->length + 1)return ERROR;
	if (L->length >= L->ListSize) {
		//空间已满，增加分配
		newbase = (ElemType*)realloc(L->elem, (L->ListSize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW);
		L->elem = newbase;
		L->ListSize += LISTINCREMENT;
	}

	/*这里还有不理解的地方，为什么动过指针移动位置，而不直接通过编号*/
	//事实证明，两种方法都可以。第一种可以参考汇编语言，基址加变址的思想。当然，所有数组的实现都是这种思想
	/*
	ElemType *p, *q;
	q = &(L->elem[i - 1]);
	for (p =&(L->elem[L->length - 1]); p >= q; --p)
		*(p + 1) = *p;

	*q = e;
     */
	int m;
	for (m = L->length - 1; m >= i-1; m--)
		L->elem[m+1] = L->elem[m];        //移动
	++L->length;
	L->elem[i - 1] = e;                   //插入
	
	return OK;
}
Status ListDelete_Sq(SqList *L, int i, ElemType *e) {
	//删除第i位置的元素，并带回其值
	ElemType *p,*q;
	if (i<1 || i>L->length)return ERROR;
	//e = L->elem[i - 1];
	p = &(L->elem[i - 1]);
	*e = *p;
	q = L->elem + L->length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L->length;
	return OK;
}

int LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	int i = 1;
	ElemType *p;
	p = L.elem;
	while (i <= L.length && !(*compare)(*p++, e))
		++i;
	if (i <= L.length)return i;
	else 0;
	
}
void ListTraverse_Sq(SqList L) {
	//打印
	int i;
	for (i = 0; i < L.length; i++)
		printf("%d ", L.elem[i]);
	printf("\n"); 
}
Status compare(ElemType x, ElemType y) {
	if (x == y)return TRUE;
	else  return FALSE;
	
}

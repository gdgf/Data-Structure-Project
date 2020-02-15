#include"Sort.h"
#include<stdio.h>
void Init(Sqlist *L)//初始化顺序表
{
	L->length = 0;
}

void Insert(Sqlist *L, int i, RedType r)//插入结点
{
	int m;
	for (m = L->length - 1; m >= i - 1; m--)
		L->r[m + 1] = L->r[m];        //移动
	++L->length;
	L->r[i - 1] = r;                   //插入
}
void print(Sqlist L)//打印静态表
{
	int i = 0;
	for (i = 1; i <L.length; i++) {
		printf("key=%d,otherinfor=%s\n", L.r[i].key, L.r[i].otherinfor);
	}
}
void InsertSort(Sqlist *L)   //直接插入排序
{
	int i = 0,j=0;
	for (i = 2; i < L->length; i++) {

		if (LT(L->r[i].key, L->r[i - 1].key)) {  //从第2个开始的元素被认为是插入值，进行比较
			L->r[0] = L->r[i];
			L->r[i] = L->r[i - 1];
			for (j = i - 2; LT(L->r[0].key, L->r[j].key);--j) {
				//寻找前面比较小的那位数字的位置，与他前面的i-2位进行比较
				L->r[j + 1] = L->r[j];               
			}
			L->r[j + 1] = L->r[0];  //插入
		}
	}
}
void BInsertSort(Sqlist *L)   //折半插入排序
{
	int i;
	for (i = 2; i < L->length; i++) {
		L->r[0] = L->r[i];
		int low = 1,high=i-1;
		while (low <= high) {
			int m=(low + high) / 2;
			if (LT(L->r[0].key, L->r[m].key))high = m - 1;
			else low = m + 1;
		}
		int j;
		for (j = i - 1; j >= high + 1; --j)
			L->r[j + 1] = L->r[j];
		L->r[high + 1] = L->r[0];
	}
}

void BubbleSort(Sqlist *L)       //冒泡排序
{
	int i, j;
	for (i = 1; i < L->length; i++) {
		//选出i~L->length中数值最小的
		for (j = i + 1; j < L->length; j++) {
			if (L->r[i].key > L->r[j].key) {
				RedType temp = L->r[i];
				L->r[i]= L->r[j];
				L->r[j] = temp;
			}
		}
	}
}
void QuickSort(Sqlist *L)        //快速排序
{
	QSort(L, 1, L->length-1);
}
void QSort(Sqlist *L,int low,int high) //快速排序
{
	if (low < high) {
		int pivotloc = Partition(L,low, high);
		QSort(L, low, pivotloc-1);
		QSort(L, pivotloc+1, high);
	}
}

int Partition(Sqlist *L, int low, int high)
{
	L->r[0] = L->r[low];
    int pivotkey = L->r[low].key;
	while (low < high)
	{
		//找到比枢轴记录小的高位
		while (low < high&&L->r[high].key >= pivotkey)
			--high;
		L->r[low] = L->r[high];

		//找到比枢轴记录大的低位
		while (low < high&&L->r[low].key <= pivotkey)
			++low;
		L->r[high] = L->r[low];
	}
	L->r[low] = L->r[0];
	return low;
}


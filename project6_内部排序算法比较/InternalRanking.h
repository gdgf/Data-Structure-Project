#ifndef INTERNALRANKING_H_INCLUDED
#define INTERNALRANKING_H_INCLUDED
typedef int Status;
#define OK 1
#define ERROR 0
#define RANGE 10000
#define ARRAY 100
int Start();//界面
Status output(int a[ARRAY]);//打印函数
void BubbleSort(int a[ARRAY]);     //起泡排序
Status insertSort(int a[ARRAY]);   //直接插入排序
Status SelectSort(int a[ARRAY]);    //简单选择排序
Status Partition(int a[ARRAY], int low, int high, int &s, int &l);//快速排序
void Qsort(int a[ARRAY], int low, int high, int &s, int &l);
void QuickSort(int a[ARRAY]);
void ShellInsert(int a[ARRAY], int d, int &s, int &l);
void ShellSort(int a[ARRAY]);       //希尔排序
void HeapAdjust(int a[ARRAY],int i,int A, int &s, int &l);
void HeapSort(int a[ARRAY]);       //堆排序
void BInsertSort(int a[ARRAY]);       //折半插入排序
void BiInsert_Sort(int a[ARRAY]);    //二路插入
void merge(int X[],int Z[],int s,int u,int v);//将有序的X[s..u]和X[u+1..v]归并为有序的Z[s..v]
void mergePass(int X[],int Y[],int n,int t);
void mergeSort(int a[ARRAY]);//二路归并排序
int GetNumInPos(int num,int pos);// 找到num的从低到高的第pos位的数据
void RadixSort(int a[ARRAY]);//基数排序
#endif // INTERNALRANKING_H_INCLUDED

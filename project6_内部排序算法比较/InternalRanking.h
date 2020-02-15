#ifndef INTERNALRANKING_H_INCLUDED
#define INTERNALRANKING_H_INCLUDED
typedef int Status;
#define OK 1
#define ERROR 0
#define RANGE 10000
#define ARRAY 100
int Start();//����
Status output(int a[ARRAY]);//��ӡ����
void BubbleSort(int a[ARRAY]);     //��������
Status insertSort(int a[ARRAY]);   //ֱ�Ӳ�������
Status SelectSort(int a[ARRAY]);    //��ѡ������
Status Partition(int a[ARRAY], int low, int high, int &s, int &l);//��������
void Qsort(int a[ARRAY], int low, int high, int &s, int &l);
void QuickSort(int a[ARRAY]);
void ShellInsert(int a[ARRAY], int d, int &s, int &l);
void ShellSort(int a[ARRAY]);       //ϣ������
void HeapAdjust(int a[ARRAY],int i,int A, int &s, int &l);
void HeapSort(int a[ARRAY]);       //������
void BInsertSort(int a[ARRAY]);       //�۰��������
void BiInsert_Sort(int a[ARRAY]);    //��·����
void merge(int X[],int Z[],int s,int u,int v);//�������X[s..u]��X[u+1..v]�鲢Ϊ�����Z[s..v]
void mergePass(int X[],int Y[],int n,int t);
void mergeSort(int a[ARRAY]);//��·�鲢����
int GetNumInPos(int num,int pos);// �ҵ�num�Ĵӵ͵��ߵĵ�posλ������
void RadixSort(int a[ARRAY]);//��������
#endif // INTERNALRANKING_H_INCLUDED

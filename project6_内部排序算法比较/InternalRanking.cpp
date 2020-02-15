#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include"InternalRanking.h"
int Start()
{
        printf("       *-----------��ϵͳ��ʾ˵��-------------*\n");
        printf("       *��������Ҫ���еĲ�������:             *\n");
        printf("       *           1:��������                 *\n");
        printf("       *           2:ֱ�Ӳ�������             *\n");
        printf("       *           3:��ѡ������             *\n");
        printf("       *           4:��������                 *\n");
        printf("       *           5:ϣ������                 *\n");
        printf("       *           6:������                   *\n");
        printf("       *           7:�۰��������             *\n");
        printf("       *           8:��·��������             *\n");
        printf("       *           9:�鲢����                 *\n");
        printf("       *           10:��������                *\n");
        printf("       *           11:һ�����������������  *\n");
        printf("       *           0:�˳�ϵͳ                 *\n");
        printf("       *--------------------------------------*\n");
    return 1;
}
Status output(int a[ARRAY])
//��ӡ����
{
    int i, k=0;
    for(i=0; i<ARRAY; i++)
    {
        printf("%6d", a[i]);
        k++;
        if(k%10==0)
        {
            printf("\n");
        }
    }
    return OK;
}
void BubbleSort(int a[ARRAY])
{//��������
    int i, j, t, s=0, l=0;
    for(i=0; i<ARRAY; i++)
    {
        for(j=0; j<(ARRAY-i); j++)
        {
            if(a[j]>a[j+1])
            {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
                l++;
            }
            s++;
        }
    }
    printf("��������\n");
    output(a);
    printf("��Ƚϴ������ƶ�������  %d  %d\n", s, l);
}
Status insertSort(int a[ARRAY])
{//ֱ�Ӳ�������
    int i, j, k, s=0, l=0;  //k��Ϊ�����ռ䣻
    for(i=1; i<ARRAY; ++i)
    {
        if(a[i]<a[i-1])
        {
            k = a[i];
            s++;
            for(j = i-1; j>=0&&a[j]>k; --j)
            {
                a[j+1] = a[j];
                l++;
            }
            a[j+1] = k;
            l++;
        }
    }
    printf("ֱ�Ӳ�������\n");
    output(a);
    printf("�Ƚϴ������ƶ�������  %d  %d\n", s, l);
    return OK;
}

Status Partition(int a[ARRAY], int low, int high, int &s, int &l)
{//��������
    int k;
    k = a[low];
    while(low < high)
    {
        while(low<high&&a[high]>=k)
        {
            high --;
            s++;
        }
        a[low] = a[high];
        while(low<high && a[low]<=k)
        {
            low ++;
            s++;
        }
        a[high] = a[low];
        s++;
    }
    a[low] = k;
    l++;
    return low;
}
void Qsort(int a[ARRAY], int low, int high, int &s, int &l)
{
    int pivoloc;
    if(low<high)
    {
        pivoloc = Partition(a, low, high, s, l);
        Qsort(a, low, pivoloc-1, s, l);
        Qsort(a, pivoloc+1, high, s, l);
    }
}
void QuickSort(int a[ARRAY])
{
    int s=0, l=0;
    Qsort(a, 0, 99, s, l);
    printf("��������\n");
    output(a);
    printf("�Ƚϴ������ƶ�������  %d  %d\n", s, l);
}
Status SelectSort(int a[ARRAY])
{//��ѡ������
    int i, j, k, l=0, s=0, t, u;
    for(i=0; i<ARRAY; i++)
    {
        k=a[i];
        u=i;
        for(j=i; j<ARRAY; j++)
        {
            s++;
            if(a[j]<k)
            {
                k = a[j];
                u = j;
            }
        }
        s++;
        if(i!=u)
        {
            t=a[i];
            a[i] = a[u];
            a[u] = t;
            l++;
        }
    }
    printf("��ѡ������\n");
    output(a);
    printf("�Ƚϴ������ƶ�������  %d  %d\n", s, l);
    return OK;
}
void ShellInsert(int a[ARRAY], int d, int &s, int &l)
{
    int i, j, k;
    for(i = d; i<ARRAY; ++i)
    {
        if(a[i]<a[i-d])
        {
            s++;
            k = a[i];
            for(j=i-d; j>=0&&k<a[j]; j-=d)
            {
                s++;
                a[j+d] = a[j];
                l++;
            }
            a[j+d] = k;
            l++;
        }
    }
}
void ShellSort(int a[ARRAY])
{//ϣ������
    int t=4, i, s=0, l=0;
    int dlta[] = {40, 13, 4, 1};
    for(i=0; i<t; i++)
    {
        ShellInsert(a, dlta[i], s, l);
    }
    printf("ϣ������\n");
    output(a);
    printf("�Ƚϴ������ƶ�������  %d  %d\n", s, l);
}
void HeapAdjust(int a[ARRAY],int i,int A, int &s, int &l)
{
    int r,j;
    r = a[i];
    for(j=2*i; j<A; j*=2)
    {
        if(j<A&&a[j]<a[j+1])  ++j;
        s++;
        if(!(r<a[j])) break;
        s++;
        a[i] = a[j];
        l++;
        i = j;
    }
    a[i] = r;
}

void HeapSort(int a[ARRAY])
{//������
    int i, t, s=0, l=0;
    for(i=ARRAY/2; i>=0; --i)
    {
        HeapAdjust(a, i, ARRAY, s, l);
    }
    for(i=ARRAY-1; i>0; --i)
    {
        t = a[0];
        a[0] = a[i];
        a[i] = t;
        l++;
        HeapAdjust(a, 0, i-1, s, l);
    }
    printf("������\n");
    output(a);
    printf("��Ƚϴ������ƶ�������  %d  %d\n", s, l);
}
void BInsertSort(int a[ARRAY])
//�۰��������
{
    int i, j, k, low, high, m,s=0,l=0;
    for(i = 1; i <ARRAY; i++) {
        low = 0;
        high = i - 1;
        while(low <= high) {
            m = (low + high) / 2;
            if(a[m] > a[i])
                high = m - 1;
            else
                low = m + 1;
            s++;
        }
        if(j!=i-1){
            int temp = a[i];
            for(k = i - 1; k >= high + 1; k--)
             {
                 a[k + 1] = a[k];
                 l++;
             }
            a[k + 1] = temp;
            l++;
        }
    }
   printf("�۰��������\n");
   output(a);
   printf("��Ƚϴ������ƶ�������  %d  %d\n", s, l);
}
void BiInsert_Sort(int a[ARRAY])
//��·����������㷨
{
    int i, first, final, k,s=0,l=0;
    int temp[ARRAY];
    first = final = 0;
    temp[0] = a[0];
    for (i = 1; i<ARRAY;i ++)
    {
          if (a[i] < temp[first])
          {      // ������Ԫ�ر���С��Ԫ��С
              first = (first - 1 + ARRAY) % ARRAY;
              temp[first] = a[i];
              l++;
              s++;
          } else if (a[i] > temp[final])
           { // ������Ԫ�ر����Ԫ�ش�
               final = (final + 1 + ARRAY) %ARRAY;
               temp[final] = a[i];
               l++;
               s++;
          } else { // ����Ԫ�ر���С�󣬱����С
               k = (final + 1 + ARRAY) % ARRAY;
               while (temp[((k - 1) + ARRAY) % ARRAY] > a[i])
               {
                  temp[(k + ARRAY) % ARRAY] =temp[(k - 1 + ARRAY) % ARRAY];
                  k = (k - 1 + ARRAY) % ARRAY;
                  s++;
                }
                temp[(k + ARRAY) % ARRAY] = a[i];
                final = (final + 1 + ARRAY) % ARRAY;
                l++;
                s++;
          }
    }
    // �������¼���Ƶ�ԭ����˳�����
    for (k = 0; k <ARRAY; k ++){
       a[k] = temp[(first + k) % ARRAY];
       l++;
    }
    printf("��·��������\n");
   output(a);
   printf("��Ƚϴ������ƶ�������  %d  %d\n", s, l);
}
void merge(int X[], int Z[], int s, int u, int v,int *m,int *n)
//�������X[s..u]��X[u+1..v]�鲢Ϊ�����Z[s..v]
{
    int i, j, q;
    i = s;
    j = u + 1;
    q = s;

    while( i <= u && j<= v )
    {
        if( X[i] <= X[j] ){
            Z[q++] = X[i++];
            (*m)++;
            (*n)++;
        }
        else{
            Z[q++] = X[j++];
            (*m)++;
            (*n)++;
        }
    }
    while( i <= u ){      //��X��ʣ��Ԫ��X[i..u]���Ƶ�Z
        Z[q++] = X[i++];
        (*n)++;
    }
    while( j <= v ) {     //��X��ʣ��Ԫ��X[j..v]���Ƶ�Z
        Z[q++] = X[j++];
        (*n)++;
    }
}
void mergePass(int X[],int Y[],int n,int t,int *s,int *l)
{
    int i = 0, j;
    while( n - i >= 2 * t )     //�����ڵ���������Ϊt�ĸ�������������кϲ���һ������Ϊ2t��������
    {
        merge(X, Y, i, i + t - 1, i + 2 * t - 1,s,l);
        i = i + 2 * t;
    }
    if( n - i > t )       //�����ʣ�µ�Ԫ�ظ�������һ�������еĳ���tʱ
        merge(X, Y, i, i + t - 1, n - 1,s,l);
    else             //n-i <= tʱ���൱��ֻ�ǰ�X[i..n-1]�����е����ݸ�ֵ��Y[i..n-1]
        for( j = i ; j < n ; ++j )
        {
            Y[j] = X[j];
            (*l)++;
        }
}
void mergeSort(int a[ARRAY])
//��·�鲢����
{
    int i=1,s=0,l=0;
    int *b= (int *)malloc(sizeof(int) *ARRAY);
    while(i<ARRAY)
    {
        mergePass(a, b, ARRAY, i,&s,&l);
        i*= 2;
        mergePass(b, a, ARRAY, i,&s,&l);
        i*= 2;
    }
    free(b);
   printf("��·�鲢����\n");
   output(a);
   printf("��Ƚϴ������ƶ�������  %d  %d\n",s,l);
}
int GetNumInPos(int num,int pos)
// �ҵ�num�Ĵӵ͵��ߵĵ�posλ������
{
    int temp = 1;
    for (int i=0; i<pos-1; i++)
        temp*=10;
    return (num/temp)%10;
}
void RadixSort(int a[ARRAY])
//��������
{
    int i,j,k,pos,num,index,s=0,l=0;
    int *b[10];        //�ֱ�Ϊ0~9�����пռ�
    for (i=0;i<10;i++)
    {
        b[i]=(int *)malloc(sizeof(int)*(ARRAY+1));
        b[i][0] = 0;    //indexΪ0����¼�������ݵĸ���
    }
    for (pos = 1; pos <=31; pos++)    //�Ӹ�λ��ʼ��31λ
    {
        for (i = 0; i <ARRAY; i++)    //�������
        {
            num = GetNumInPos(a[i], pos);
            index = ++b[num][0];
            b[num][index] = a[i];
            l++;
        }
        for (i = 0,j=0;i <10;i++)    //�ռ�
        {
            for (k = 1; k<=b[i][0];k++)
             {
                 a[j++]=b[i][k];
                 s++;
             }
            b[i][0]=0;
        }
    }
    printf("��������\n");
    output(a);
    printf("��Ƚϴ������ƶ�������  %d  %d\n", s, l);
}

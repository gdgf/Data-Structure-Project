#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include"InternalRanking.h"
int main()
{
    int a[100],b[100],c[100],d[100],e[100],f[100],g[100],h[100],p[100],q[100];
    int i,Command;
    while(1){
        Start();
        for(i=0; i<100; i++)
           a[i]=rand()%RANGE;
        printf("原始数据如下:\n");
        output(a);
        printf("请输入你要进行的步骤:");
        scanf("%d",&Command);
        getchar();
        switch(Command){
        case 1:
              BubbleSort(a);          //起泡排序
              break;
         case 2:
              insertSort(a);          //直接插入排序
              break;
         case 3:
                SelectSort(a);          //简单选择排序
              break;
         case 4:
                QuickSort(a);           //快速排序
              break;
         case 5:
                ShellSort(a);           //希尔排序
               break;
        case 6:
                HeapSort(a);           //堆排序
               break;
        case 7:
               BInsertSort(a);          //折半插入排序
               break;
        case 8:
               BiInsert_Sort(a);        //二路插入排序
               break;
        case 9:
               mergeSort(a);            //二路归并排序
               break;
        case 10:
               RadixSort(a);            //基数排序
               break;
        case 11:
            for(i=0;i<ARRAY;i++)
            {
                b[i]=c[i]=d[i]=e[i]=f[i]=g[i]=h[i]=p[i]=q[i]=a[i];
            }
            BubbleSort(a);          //起泡排序
            insertSort(b);          //直接插入排序
            SelectSort(c);          //简单选择排序
            QuickSort(d);           //快速排序
            ShellSort(e);           //希尔排序
            HeapSort(f);            //堆排序
            BInsertSort(g);          //折半插入排序
            BiInsert_Sort(h);        //二路插入排序
            mergeSort(p);            //二路归并排序
           RadixSort(q);             //基数排序
            break;
        case 0:
              return 0;
       }
    }
    return 0;
}



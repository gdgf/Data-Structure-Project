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
        printf("ԭʼ��������:\n");
        output(a);
        printf("��������Ҫ���еĲ���:");
        scanf("%d",&Command);
        getchar();
        switch(Command){
        case 1:
              BubbleSort(a);          //��������
              break;
         case 2:
              insertSort(a);          //ֱ�Ӳ�������
              break;
         case 3:
                SelectSort(a);          //��ѡ������
              break;
         case 4:
                QuickSort(a);           //��������
              break;
         case 5:
                ShellSort(a);           //ϣ������
               break;
        case 6:
                HeapSort(a);           //������
               break;
        case 7:
               BInsertSort(a);          //�۰��������
               break;
        case 8:
               BiInsert_Sort(a);        //��·��������
               break;
        case 9:
               mergeSort(a);            //��·�鲢����
               break;
        case 10:
               RadixSort(a);            //��������
               break;
        case 11:
            for(i=0;i<ARRAY;i++)
            {
                b[i]=c[i]=d[i]=e[i]=f[i]=g[i]=h[i]=p[i]=q[i]=a[i];
            }
            BubbleSort(a);          //��������
            insertSort(b);          //ֱ�Ӳ�������
            SelectSort(c);          //��ѡ������
            QuickSort(d);           //��������
            ShellSort(e);           //ϣ������
            HeapSort(f);            //������
            BInsertSort(g);          //�۰��������
            BiInsert_Sort(h);        //��·��������
            mergeSort(p);            //��·�鲢����
           RadixSort(q);             //��������
            break;
        case 0:
              return 0;
       }
    }
    return 0;
}



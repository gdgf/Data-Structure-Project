#include"LinkList.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
      int i;   //������
      int N;   //���������
      int m;   //��ʼ����
      int p;   //��������
      int MaxP;//��������

      printf("�����뱨�����ޣ�");
      scanf("%d",&MaxP);
      printf("���������������");
      scanf("%d",&N);
      printf("�������ʼ���룺");
      scanf("%d",&m);
       while(p>MaxP)
         {
             printf("���볬����Χ�����������룺");
             scanf("%d",&p);
         }

      //��ʼ��
      JoseNode *h=JoseInit();

      //��������
      printf("��������%d���˵�����:\n",N);
      for (i = 1; i <=N; i++)
       {
         scanf("%d",&p);
         while(p>MaxP)
         {
             printf("���볬����Χ�����������룺");
             scanf("%d",&p);
         }
         JoseInsert(h, i, i,p);
       }

       //����
       TraverseList(h,N);

       //����
       printf("����˳��Ϊ��");
       Column(h,m);
       printf("\n");
       return 0;
 }

#include"LinkList.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
      int i;   //计数器
      int N;   //参与的人数
      int m;   //初始密码
      int p;   //个人密码
      int MaxP;//报数上限

      printf("请输入报数上限：");
      scanf("%d",&MaxP);
      printf("请输入参与人数：");
      scanf("%d",&N);
      printf("请输入初始密码：");
      scanf("%d",&m);
       while(p>MaxP)
         {
             printf("密码超过范围，请重新输入：");
             scanf("%d",&p);
         }

      //初始化
      JoseNode *h=JoseInit();

      //数据输入
      printf("请输入这%d个人的密码:\n",N);
      for (i = 1; i <=N; i++)
       {
         scanf("%d",&p);
         while(p>MaxP)
         {
             printf("密码超过范围，请重新输入：");
             scanf("%d",&p);
         }
         JoseInsert(h, i, i,p);
       }

       //遍历
       TraverseList(h,N);

       //出列
       printf("出列顺序为：");
       Column(h,m);
       printf("\n");
       return 0;
 }

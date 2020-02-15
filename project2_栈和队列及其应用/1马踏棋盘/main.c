#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <math.h>
int cheesboard[8][8];
int Htry1[8]={-2,-1,1,2,2,1,-1,-2};
int Htry2[8]={1,2,2,1,-1,-2,-2,-1};  //二维数组存储马行走的路径的定义
int main()
{
	int i,j;
	scanf("%d,%d",&i,&j);
	if(i<=8&&j<=8&&j>=1&&i>=1)    //判断输入数据的正误
	  getPath(cheesboard,j-1,i-1);
	else
      printf("ERROR!");
	return 0;
}

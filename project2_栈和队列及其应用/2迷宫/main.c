#include<stdio.h>
#include<stdlib.h>
#include "HEAD.h"
int main()
{
    int row,col;
    printf("请输入迷宫的行数及列数\n");
    scanf("%d%d",&row,&col);
    printf("请输入%d行%d列数组建立迷宫\n",row,col);
    build(row,col);     //建立迷宫
    int p,q;
    printf("迷宫建立完成\n");
    for(p=0;p<=row+1;p++){
        for(q=0;q<=col+1;q++){
            printf("%d ",a[p][q].m);
        }
        printf("\n");
    }
    int g1,g2,h1,h2;
    printf("请输入迷宫起点坐标，中间用空格隔开\n");
    scanf("%d%d",&g1,&g2);   //输入起点，若错误重输
    while(g1<1||g1>row||g2<1||g2>col){
        printf("输入错误，请重新输入\n");
        scanf("%d%d",&g1,&g2);
    }
    printf("请输入迷宫终点坐标，中间用空格隔开\n");
    scanf("%d%d",&h1,&h2);
    while(h1<1||h1>row||h2<1||h2>col||(h1==g1&&h2==g2)){
        printf("输入错误，请重新输入\n");
        scanf("%d%d",&h1,&h2);
    }
    check(g1,g2,h1,h2,row,col);
    return 0;
}

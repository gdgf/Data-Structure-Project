#include<stdio.h>
#include<stdlib.h>
#include "HEAD.h"
int main()
{
    int row,col;
    printf("�������Թ�������������\n");
    scanf("%d%d",&row,&col);
    printf("������%d��%d�����齨���Թ�\n",row,col);
    build(row,col);     //�����Թ�
    int p,q;
    printf("�Թ��������\n");
    for(p=0;p<=row+1;p++){
        for(q=0;q<=col+1;q++){
            printf("%d ",a[p][q].m);
        }
        printf("\n");
    }
    int g1,g2,h1,h2;
    printf("�������Թ�������꣬�м��ÿո����\n");
    scanf("%d%d",&g1,&g2);   //������㣬����������
    while(g1<1||g1>row||g2<1||g2>col){
        printf("�����������������\n");
        scanf("%d%d",&g1,&g2);
    }
    printf("�������Թ��յ����꣬�м��ÿո����\n");
    scanf("%d%d",&h1,&h2);
    while(h1<1||h1>row||h2<1||h2>col||(h1==g1&&h2==g2)){
        printf("�����������������\n");
        scanf("%d%d",&h1,&h2);
    }
    check(g1,g2,h1,h2,row,col);
    return 0;
}

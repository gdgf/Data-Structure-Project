#include<stdlib.h>
#include<stdio.h>
#include"M_Arithemetic.h"
/****稀疏矩阵类型定义****/
#define MaxSize 200
typedef int DataType;
typedef struct
{
    int i,j;
    DataType e;
}Triple;                  //三元组类型定义
struct TriSeqMatrix		  //矩阵类型定义
{
    Triple data[MaxSize]; //非0元三元组
	int rpos[MaxSize];    //各行中第一个非0元的位置
    int m,n,len; 		  //矩阵的行数，列数和非零元素的个数
};
int main()
{
    printf("---------------------稀疏矩阵运算器----------------------------\n");
    printf("|  你要进行矩阵的那种运算？                                    |\n");
    printf("|  加法请输入+,减法请输入-，乘法请输入*                        |\n");
    printf("------------------—-(输入0退出系统)---------------------------\n:");
    char c;
	TriSeqMatrix A,B,C;
	do{
        scanf("%c",&c);
        if(c=='+'){
            CreateMatrix(&A);
            PrintMatrix(A);
            CreateMatrix(&B);
            PrintMatrix(B);
            AddMatrix(A,B,&C);
            printf("下面是以上两个矩阵通过加法运算所得矩阵的详细情况：\n");
            PrintMatrix(C);
            getchar();
            printf(":");
        }else if(c=='-'){
            CreateMatrix(&A);
            PrintMatrix(A);
            CreateMatrix(&B);
            PrintMatrix(B);
            SubMatrix(A,B,&C);
            printf("下面是以上两个矩阵通过减法运算所得矩阵的详细情况：\n");
            PrintMatrix(C);
            getchar();
            printf(":");
        }else if(c=='*'){
            CreateMatrix(&A);
            PrintMatrix(A);
            CreateMatrix(&B);
            PrintMatrix(B);
            MultMatrix(A,B,&C);
            printf("下面是以上两个矩阵通过乘法运算所得矩阵的详细情况：\n");
            PrintMatrix(C);
            getchar();
            printf(":");
        }else if(c=='0')
            return 0;
        else{
            printf("输入运算符错误!,请重新输入\n");
            printf(":");
            getchar();
        }
	 }while(1);
    return 0;
}

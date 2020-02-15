#include<stdlib.h>
#include<stdio.h>
#include"M_Arithemetic.h"
/****ϡ��������Ͷ���****/
#define MaxSize 200
typedef int DataType;
typedef struct
{
    int i,j;
    DataType e;
}Triple;                  //��Ԫ�����Ͷ���
struct TriSeqMatrix		  //�������Ͷ���
{
    Triple data[MaxSize]; //��0Ԫ��Ԫ��
	int rpos[MaxSize];    //�����е�һ����0Ԫ��λ��
    int m,n,len; 		  //����������������ͷ���Ԫ�صĸ���
};
int main()
{
    printf("---------------------ϡ�����������----------------------------\n");
    printf("|  ��Ҫ���о�����������㣿                                    |\n");
    printf("|  �ӷ�������+,����������-���˷�������*                        |\n");
    printf("------------------��-(����0�˳�ϵͳ)---------------------------\n:");
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
            printf("������������������ͨ���ӷ��������þ������ϸ�����\n");
            PrintMatrix(C);
            getchar();
            printf(":");
        }else if(c=='-'){
            CreateMatrix(&A);
            PrintMatrix(A);
            CreateMatrix(&B);
            PrintMatrix(B);
            SubMatrix(A,B,&C);
            printf("������������������ͨ�������������þ������ϸ�����\n");
            PrintMatrix(C);
            getchar();
            printf(":");
        }else if(c=='*'){
            CreateMatrix(&A);
            PrintMatrix(A);
            CreateMatrix(&B);
            PrintMatrix(B);
            MultMatrix(A,B,&C);
            printf("������������������ͨ���˷��������þ������ϸ�����\n");
            PrintMatrix(C);
            getchar();
            printf(":");
        }else if(c=='0')
            return 0;
        else{
            printf("�������������!,����������\n");
            printf(":");
            getchar();
        }
	 }while(1);
    return 0;
}

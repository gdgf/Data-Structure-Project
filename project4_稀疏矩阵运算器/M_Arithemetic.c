#include"M_Arithemetic.h"
#include<stdlib.h>
#include<stdio.h>

#define OK 1
#define ERROR  0
/****稀疏矩阵类型定义****/
#define MaxSize 200
typedef int DataType;
typedef struct
{
    int i,j;              //非0元素的行、列
    DataType e;
}Triple;                  //三元组类型定义
struct TriSeqMatrix		  //矩阵类型定义
{
    Triple data[MaxSize]; //非0元三元组
	int rpos[MaxSize];    //各行中第一个非0元的位置
    int m,n,len; 		  //矩阵的行数，列数和非零元素的个数
};
int CreateMatrix(TriSeqMatrix *M)
//创建稀疏矩阵（按照行优先顺序输入非零元素值）
{
	int i,m,n,flag;
	DataType e;
	//定义矩阵
	printf("请输入稀疏矩阵的行数,列数,非0元素个数:");
	scanf("%d,%d,%d",&M->m,&M->n,&M->len);
	//非0元素不会超过数据域的最大值
	if(M->len>MaxSize)
		return ERROR;
	//数据输入
	for(i=0;i<M->len;i++){
		do{
	        printf("请按行序顺序输入第%d个非0元素所在的行(0~%d),列(0~%d),元素值:",
                i+1,M->m-1,M->n-1);
            scanf("%d,%d,%d",&m,&n,&e);
			flag=0;							//初始化标志位
			//如果行号或列号错误，标志位为1
			if((m<0||m>M->m)||(n<0||n>M->n))
	            flag=1;
            //若输入的顺序错误，则标志位为1
			if(i>0&&(m<M->data[i-1].i||m==M->data[i-1].i)&&(n<=M->data[i-1].j))
				flag=1;
            if(flag==1)
                printf("输入的行/列号有误，或者输入的顺序有误，请重新输入!\n");
		}while(flag);
		M->data[i].i=m;
		M->data[i].j=n;
		M->data[i].e=e;
	}
	return OK;
}
void PrintMatrix(TriSeqMatrix M)
//输出矩阵
{
    int i,a,b,p,q;
    a=M.m;
    b=M.n;
    //先构造一个一般矩阵A，并初始化
    int W[a][b];
    //赋值
    for(p=0;p<M.m;p++)
         for(q=0;q<M.n;q++)
           W[p][q]=0;
    for(i=0;i<M.len;i++)
        W[M.data[i].i][M.data[i].j]=M.data[i].e;
    //输出
    printf("稀疏矩阵是%d行*%d列，共%d个非0元素\n",M.m,M.n,M.len);
    for(p=0;p<M.m;p++){
         for(q=0;q<M.n;q++){
           printf("%3d",W[p][q]);
        }
        printf("\n");
    }
}
int CompareElement(int a,int b)
//比较两个矩阵的元素值大小。前者小于后者，返回-1；相等，返回0；大于，返回1
{
	if(a<b)
		return -1;
	if(a==b)
		return 0;
	return 1;
}
int AddMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C)
//将两个矩阵A和B对应的元素值相加，得到另一个稀疏矩阵C
{
	int m=0,n=0,k=-1;
	if(A.m!=B.m||A.n!=B.n){ //如果两个矩阵的行数与列数不相等，则不能够进行相加运算
        printf("输入的两矩阵的行数/列数不相等，不能进行加/减法运算！");
        return ERROR;
    }
    //初始化C
	C->m=A.m;
	C->n=A.n;
	while(m<A.len&&n<B.len){
		switch(CompareElement(A.data[m].i,B.data[n].i)){ //比较两个矩阵对应元素的行号
            case -1:
                C->data[++k]=A.data[m++];	//将矩阵A，即行号小的元素赋值给C
                break;
            case  0://如果矩阵A和B的行号相等，则比较列号
                switch(CompareElement(A.data[m].j,B.data[n].j)){
                    case -1:					//如果A的列号小于B的列号，则将矩阵A的元素赋值给C
                        C->data[++k]=A.data[m++];
                        break;
                    case  0:					//如果A和B的行号、列号均相等，则将两元素相加，存入C
                        C->data[++k]=A.data[m++];
                        C->data[k].e+=B.data[n++].e;
                        if(C->data[k].e==0)		//如果两个元素的和为0，则不保存
                            k--;
                        break;
                    case  1:					//如果A的列号大于B的列号，则将矩阵B的元素赋值给C
                        C->data[++k]=B.data[n++];
                }
                break;
            case  1:						//如果A的行号大于B的行号，则将矩阵B的元素赋值给C
                C->data[++k]=B.data[n++];
		}
	}
	while(m<A.len)						//如果矩阵A的元素还没处理完毕，则将A中的元素赋值给C
		C->data[++k]=A.data[m++];
	while(n<B.len)						//如果矩阵B的元素还没处理完毕，则将B中的元素赋值给C
		C->data[++k]=B.data[n++];
	C->len=k+1;							//修改非零元素的个数
	if(k>MaxSize)
		return ERROR;
	return OK;
}
int SubMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C)
//将两个矩阵A和B对应的元素值相减，得到另一个稀疏矩阵C
{
	int i,k;
	for(i=0;i<B.len;i++)
        B.data[i].e*=-1;        //减法和加法性质相同
     k=AddMatrix(A,B,C);
     return k;
}
void MultMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C)
//稀疏矩阵A和B相乘得到C
{
	int i,k,tp,tq,p,q,arow,brow,ccol;
	int temp[MaxSize];
	int num[MaxSize];           //每一行非0元的个数

	if(A.n!=B.m){				//如果矩阵A的列与B的行不相等，则返回
        printf("矩阵A的列与B的行不相等,不能进行矩阵乘法！");
		return ;
	}
    //初始化C的行数、列数和非零元素的个数
	C->m=A.m;
	C->n=B.n;
	C->len=0;

	if(A.len*B.len==0){			//只要有一个矩阵的长度为0，则返回
	    printf("矩阵A/B没有非0元素，相乘元素全为0");
		return ;
	}
	//求矩阵A中每一行第一个非零元素的位置
	for(i=0;i<A.m;i++)			//初始化化num
		num[i]=0;
	for(k=0;k<A.len;k++){      //每一行中非0元的个数
		i=A.data[k].i;
		num[i]++;
	}
	A.rpos[0]=0;
	for(i=1;i<A.m;i++)			//rpos存放矩阵A中每一行第一个非零元素的位置
		A.rpos[i]=A.rpos[i-1]+num[i-1];

    //求矩阵B中每一行第一个非零元素的位置
	for(i=0;i<B.m;i++)			//初始化num
		num[i]=0;
	for(k=0;k<B.len;k++){		//num存放矩阵B中每一行非零元素的个数
		i=B.data[k].i;
		num[i]++;
	}
	B.rpos[0]=0;
	for(i=1;i<B.m;i++)			//rpos存放矩阵B中每一行第一个非零元素的位置
		B.rpos[i]=B.rpos[i-1]+num[i-1];


	//计算两个矩阵的乘积
	//arow:行
	for(arow=0;arow<A.m;arow++){	//依次扫描矩阵A的每一行
		for(i=0;i<B.n;i++)
			temp[i]=0;
		C->rpos[arow]=C->len;       //c的第arow行的第一个非0元素的位置
		//对每个非0元处理
		if(arow<A.m-1)              //边界限制
			tp=A.rpos[arow+1];
		else
			tp=A.len;
       //p从A的第i行的第一个非0元的位置起到底第i+1行的第一个非0元的位置
		for(p=A.rpos[arow];p<tp;p++){
			brow=A.data[p].j;		        //取出A中的列号
			if(brow<B.m-1)                  //边界限制
				tq=B.rpos[brow+1];
			else
				tq=B.len;
			for(q=B.rpos[brow];q<tq;q++){	//依次取出B中的第brow行，与A中的元素相乘
				ccol=B.data[q].j;
				temp[ccol]+=A.data[p].e*B.data[q].e;
                                            //把乘积存入temp中
			}
		}
		for(ccol=0;ccol<C->n;ccol++)       //将temp中元素依次赋值给C
			if(temp[ccol]){
				if(++C->len>MaxSize)
					return  ;
				C->data[C->len-1].i=arow;
				C->data[C->len-1].j=ccol;
				C->data[C->len-1].e=temp[ccol];
			}
    }
}

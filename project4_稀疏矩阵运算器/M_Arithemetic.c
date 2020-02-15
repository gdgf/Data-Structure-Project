#include"M_Arithemetic.h"
#include<stdlib.h>
#include<stdio.h>

#define OK 1
#define ERROR  0
/****ϡ��������Ͷ���****/
#define MaxSize 200
typedef int DataType;
typedef struct
{
    int i,j;              //��0Ԫ�ص��С���
    DataType e;
}Triple;                  //��Ԫ�����Ͷ���
struct TriSeqMatrix		  //�������Ͷ���
{
    Triple data[MaxSize]; //��0Ԫ��Ԫ��
	int rpos[MaxSize];    //�����е�һ����0Ԫ��λ��
    int m,n,len; 		  //����������������ͷ���Ԫ�صĸ���
};
int CreateMatrix(TriSeqMatrix *M)
//����ϡ����󣨰���������˳���������Ԫ��ֵ��
{
	int i,m,n,flag;
	DataType e;
	//�������
	printf("������ϡ����������,����,��0Ԫ�ظ���:");
	scanf("%d,%d,%d",&M->m,&M->n,&M->len);
	//��0Ԫ�ز��ᳬ������������ֵ
	if(M->len>MaxSize)
		return ERROR;
	//��������
	for(i=0;i<M->len;i++){
		do{
	        printf("�밴����˳�������%d����0Ԫ�����ڵ���(0~%d),��(0~%d),Ԫ��ֵ:",
                i+1,M->m-1,M->n-1);
            scanf("%d,%d,%d",&m,&n,&e);
			flag=0;							//��ʼ����־λ
			//����кŻ��кŴ��󣬱�־λΪ1
			if((m<0||m>M->m)||(n<0||n>M->n))
	            flag=1;
            //�������˳��������־λΪ1
			if(i>0&&(m<M->data[i-1].i||m==M->data[i-1].i)&&(n<=M->data[i-1].j))
				flag=1;
            if(flag==1)
                printf("�������/�к����󣬻��������˳����������������!\n");
		}while(flag);
		M->data[i].i=m;
		M->data[i].j=n;
		M->data[i].e=e;
	}
	return OK;
}
void PrintMatrix(TriSeqMatrix M)
//�������
{
    int i,a,b,p,q;
    a=M.m;
    b=M.n;
    //�ȹ���һ��һ�����A������ʼ��
    int W[a][b];
    //��ֵ
    for(p=0;p<M.m;p++)
         for(q=0;q<M.n;q++)
           W[p][q]=0;
    for(i=0;i<M.len;i++)
        W[M.data[i].i][M.data[i].j]=M.data[i].e;
    //���
    printf("ϡ�������%d��*%d�У���%d����0Ԫ��\n",M.m,M.n,M.len);
    for(p=0;p<M.m;p++){
         for(q=0;q<M.n;q++){
           printf("%3d",W[p][q]);
        }
        printf("\n");
    }
}
int CompareElement(int a,int b)
//�Ƚ����������Ԫ��ֵ��С��ǰ��С�ں��ߣ�����-1����ȣ�����0�����ڣ�����1
{
	if(a<b)
		return -1;
	if(a==b)
		return 0;
	return 1;
}
int AddMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C)
//����������A��B��Ӧ��Ԫ��ֵ��ӣ��õ���һ��ϡ�����C
{
	int m=0,n=0,k=-1;
	if(A.m!=B.m||A.n!=B.n){ //��������������������������ȣ����ܹ������������
        printf("����������������/��������ȣ����ܽ��м�/�������㣡");
        return ERROR;
    }
    //��ʼ��C
	C->m=A.m;
	C->n=A.n;
	while(m<A.len&&n<B.len){
		switch(CompareElement(A.data[m].i,B.data[n].i)){ //�Ƚ����������ӦԪ�ص��к�
            case -1:
                C->data[++k]=A.data[m++];	//������A�����к�С��Ԫ�ظ�ֵ��C
                break;
            case  0://�������A��B���к���ȣ���Ƚ��к�
                switch(CompareElement(A.data[m].j,B.data[n].j)){
                    case -1:					//���A���к�С��B���кţ��򽫾���A��Ԫ�ظ�ֵ��C
                        C->data[++k]=A.data[m++];
                        break;
                    case  0:					//���A��B���кš��кž���ȣ�����Ԫ����ӣ�����C
                        C->data[++k]=A.data[m++];
                        C->data[k].e+=B.data[n++].e;
                        if(C->data[k].e==0)		//�������Ԫ�صĺ�Ϊ0���򲻱���
                            k--;
                        break;
                    case  1:					//���A���кŴ���B���кţ��򽫾���B��Ԫ�ظ�ֵ��C
                        C->data[++k]=B.data[n++];
                }
                break;
            case  1:						//���A���кŴ���B���кţ��򽫾���B��Ԫ�ظ�ֵ��C
                C->data[++k]=B.data[n++];
		}
	}
	while(m<A.len)						//�������A��Ԫ�ػ�û������ϣ���A�е�Ԫ�ظ�ֵ��C
		C->data[++k]=A.data[m++];
	while(n<B.len)						//�������B��Ԫ�ػ�û������ϣ���B�е�Ԫ�ظ�ֵ��C
		C->data[++k]=B.data[n++];
	C->len=k+1;							//�޸ķ���Ԫ�صĸ���
	if(k>MaxSize)
		return ERROR;
	return OK;
}
int SubMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C)
//����������A��B��Ӧ��Ԫ��ֵ������õ���һ��ϡ�����C
{
	int i,k;
	for(i=0;i<B.len;i++)
        B.data[i].e*=-1;        //�����ͼӷ�������ͬ
     k=AddMatrix(A,B,C);
     return k;
}
void MultMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C)
//ϡ�����A��B��˵õ�C
{
	int i,k,tp,tq,p,q,arow,brow,ccol;
	int temp[MaxSize];
	int num[MaxSize];           //ÿһ�з�0Ԫ�ĸ���

	if(A.n!=B.m){				//�������A������B���в���ȣ��򷵻�
        printf("����A������B���в����,���ܽ��о���˷���");
		return ;
	}
    //��ʼ��C�������������ͷ���Ԫ�صĸ���
	C->m=A.m;
	C->n=B.n;
	C->len=0;

	if(A.len*B.len==0){			//ֻҪ��һ������ĳ���Ϊ0���򷵻�
	    printf("����A/Bû�з�0Ԫ�أ����Ԫ��ȫΪ0");
		return ;
	}
	//�����A��ÿһ�е�һ������Ԫ�ص�λ��
	for(i=0;i<A.m;i++)			//��ʼ����num
		num[i]=0;
	for(k=0;k<A.len;k++){      //ÿһ���з�0Ԫ�ĸ���
		i=A.data[k].i;
		num[i]++;
	}
	A.rpos[0]=0;
	for(i=1;i<A.m;i++)			//rpos��ž���A��ÿһ�е�һ������Ԫ�ص�λ��
		A.rpos[i]=A.rpos[i-1]+num[i-1];

    //�����B��ÿһ�е�һ������Ԫ�ص�λ��
	for(i=0;i<B.m;i++)			//��ʼ��num
		num[i]=0;
	for(k=0;k<B.len;k++){		//num��ž���B��ÿһ�з���Ԫ�صĸ���
		i=B.data[k].i;
		num[i]++;
	}
	B.rpos[0]=0;
	for(i=1;i<B.m;i++)			//rpos��ž���B��ÿһ�е�һ������Ԫ�ص�λ��
		B.rpos[i]=B.rpos[i-1]+num[i-1];


	//������������ĳ˻�
	//arow:��
	for(arow=0;arow<A.m;arow++){	//����ɨ�����A��ÿһ��
		for(i=0;i<B.n;i++)
			temp[i]=0;
		C->rpos[arow]=C->len;       //c�ĵ�arow�еĵ�һ����0Ԫ�ص�λ��
		//��ÿ����0Ԫ����
		if(arow<A.m-1)              //�߽�����
			tp=A.rpos[arow+1];
		else
			tp=A.len;
       //p��A�ĵ�i�еĵ�һ����0Ԫ��λ���𵽵׵�i+1�еĵ�һ����0Ԫ��λ��
		for(p=A.rpos[arow];p<tp;p++){
			brow=A.data[p].j;		        //ȡ��A�е��к�
			if(brow<B.m-1)                  //�߽�����
				tq=B.rpos[brow+1];
			else
				tq=B.len;
			for(q=B.rpos[brow];q<tq;q++){	//����ȡ��B�еĵ�brow�У���A�е�Ԫ�����
				ccol=B.data[q].j;
				temp[ccol]+=A.data[p].e*B.data[q].e;
                                            //�ѳ˻�����temp��
			}
		}
		for(ccol=0;ccol<C->n;ccol++)       //��temp��Ԫ�����θ�ֵ��C
			if(temp[ccol]){
				if(++C->len>MaxSize)
					return  ;
				C->data[C->len-1].i=arow;
				C->data[C->len-1].j=ccol;
				C->data[C->len-1].e=temp[ccol];
			}
    }
}

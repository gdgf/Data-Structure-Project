#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
void initBoard(int board[][8])// ��������
{
    int i,j;
	for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            board[i][j]=0;
        }
	}
}
int getMinPath(int a[],int num)  //�������²����ٿ����Ե�̰���㷨
{
	int i=0,index=0;             //indexΪ���²����ٿ����ԵĴ洢ֵ
    int min=a[0];
    for(i=0;i<num;i++)
    {
        if(a[i]>0)               //����һ������0�ĸ�ֵ��min �� index
        {
            min=a[i];
            index=i;
            break;
        }
    }
    for(i=index+1;i<num;i++)     //���бȽϣ����ٿ����Ե�iֵ��ֵ��index
    {
        if(a[i]>0&&min>a[i])
        {
            min=a[i];
            index=i;
        }
    }
    if(a[index]>0)
        return index;            //�����С�����Ե�iֵ
    return -1;
}
void printPath(int board[][8]) //��ӡ·���ĺ���
{
    int i,j;
	for(i=0;i<8;i++)
        {
		for(j=0;j<8;j++)
		{
			printf("%d  ",board[i][j]);
		}
		printf("\n\n");
	}
}
void getPath(int board[][8],int startX, int startY) //���ĺ��� ��ȡ���·��
{
	int next=0;
	int min;
	int nextNext;
	initBoard(board);                               //��������
    int nextNum[8]={0,0,0,0,0,0,0,0};
	int nextX[8]={0,0,0,0,0,0,0,0};                 //������ȫ����Ϊδ���ߵ�״̬
    int nextY[8]={0,0,0,0,0,0,0,0};
	board [startX][startY]=1;                       //��ʼ������·��Ϊ1
	int m,i,j;                                      //��ʼ��ѭ������ֵ����
    int Htry1[8]={-2,-1,1,2,2,1,-1,-2};             //����������߹���
    int Htry2[8]={1,2,2,1,-1,-2,-2,-1};
	for(m=1;m<64;m++){
        next=0;
        for(i=0;i<8;i++){
            if(startX+Htry1[i]<0||startX+Htry1[i]>=8||
               startY+Htry2[i]<0||startY+Htry2[i]>=8||
               board[startX+Htry1[i]][startY+Htry2[i]]!=0){
                continue;                           //�ų����
            }
            nextX[next]=startX+Htry1[i];            //��һ��·��
            nextY[next]=startY+Htry2[i];
            next++;
        }if(next==1){                       //̤����һ��
		    min=0;
            startX=nextX[min];
            startY=nextY[min];
            board[startX][startY]=m+1;
        }else if(next==0){
            printf("Error!\n");
            break;
        }else{
            for(i=0;i<next;i++){
                nextNext=0;
                for(j=0;j<8;j++){
                    if(nextX[i]+Htry1[j]>=0&&nextX[i]+Htry1[j]<8&&
                       nextY[i]+Htry2[j]>=0&&nextY[i]+Htry2[j]<8&&
                       board[nextX[i]+Htry1[j]][nextY[i]+Htry2[j]]==0){
                            nextNext++;
                    }
                }
                nextNum[i]=nextNext;
            }
            if((min=getMinPath(nextNum,next))>=0){ //����̰���㷨�����²�����·��
                startX=nextX[min];
                startY=nextY[min];
                board[startX][startY]=m+1;
            }else{
                printf("Error!\n");
                break;
            }
        }
    }
    printPath(board);
}
#endif // BOARD_H_INCLUDED

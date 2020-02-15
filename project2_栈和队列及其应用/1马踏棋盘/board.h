#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
void initBoard(int board[][8])// 构建棋盘
{
    int i,j;
	for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            board[i][j]=0;
        }
	}
}
int getMinPath(int a[],int num)  //分析下下步最少可能性的贪心算法
{
	int i=0,index=0;             //index为下下步最少可能性的存储值
    int min=a[0];
    for(i=0;i<num;i++)
    {
        if(a[i]>0)               //将第一个大于0的赋值给min 和 index
        {
            min=a[i];
            index=i;
            break;
        }
    }
    for(i=index+1;i<num;i++)     //进行比较，最少可能性的i值赋值给index
    {
        if(a[i]>0&&min>a[i])
        {
            min=a[i];
            index=i;
        }
    }
    if(a[index]>0)
        return index;            //输出最小可能性的i值
    return -1;
}
void printPath(int board[][8]) //打印路径的函数
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
void getPath(int board[][8],int startX, int startY) //核心函数 获取马的路径
{
	int next=0;
	int min;
	int nextNext;
	initBoard(board);                               //定义棋盘
    int nextNum[8]={0,0,0,0,0,0,0,0};
	int nextX[8]={0,0,0,0,0,0,0,0};                 //将棋盘全部定为未行走的状态
    int nextY[8]={0,0,0,0,0,0,0,0};
	board [startX][startY]=1;                       //初始化输入路径为1
	int m,i,j;                                      //初始化循环、赋值参数
    int Htry1[8]={-2,-1,1,2,2,1,-1,-2};             //定义马的行走规则
    int Htry2[8]={1,2,2,1,-1,-2,-2,-1};
	for(m=1;m<64;m++){
        next=0;
        for(i=0;i<8;i++){
            if(startX+Htry1[i]<0||startX+Htry1[i]>=8||
               startY+Htry2[i]<0||startY+Htry2[i]>=8||
               board[startX+Htry1[i]][startY+Htry2[i]]!=0){
                continue;                           //排除误差
            }
            nextX[next]=startX+Htry1[i];            //下一步路径
            nextY[next]=startY+Htry2[i];
            next++;
        }if(next==1){                       //踏出第一步
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
            if((min=getMinPath(nextNum,next))>=0){ //运行贪心算法求下下步最少路径
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

#include <iostream>  
#include <string>  
#include <cstring>  
#include <cmath>  
#include <vector>  
#include <queue>  
#include <set>   
#include <fstream>

//通过求初始格局和目标格局逆序数，然后在比较两者的逆序数的奇偶性是否相同，如果奇偶性相同，则可以从初始格局变到目标格局。
using namespace std;
#define N 9  
int jc[N + 1] = { 1,1,2,6,24,120,720,5040,40320,362880 };//0-9的阶乘  
typedef struct data
{
	int arr[N];//格局  
	int hash;  //存储某一格局的哈希  
	int pos;   //0当前位置  
	int step;  //记录步数  
}Node;

int dir[4][2] = {    //从左边开始顺时针旋转  
	{ -1,0 },
    { 0,-1 },
    { 1,0 },
    { 0,1 }
};

/**
*  康托展开
*/
int cantor(int arr[N])
{
	int i, j;
	int sum = 0;
	for (i = 0; i<N; i++)
	{
		int nmin = 0;
		//求逆序数
		for (j = i + 1; j<N; j++)
		{
			if (arr[i]>arr[j])
				nmin++;
		}
		sum += (nmin*jc[N - i - 1]);

	}
	return sum;
}

/**
*数据交换
*/
void swap(int *arr, int i, int j)
{
	int t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}

/**
* 打印数组，测试用
*/
void printArray(int * arr)
{
	int i, j;
	for (i = 0; i<N; i++)
	{
		if (i % 3 == 0)
			cout << "\n";
		cout << arr[i] << " ";
	}
	cout << endl;
}

/**
* 复制数组
*/
void copyArray(int src[N], int target[N])
{
	int i;
	for (i = 0; i<N; i++)
	{
		target[i] = src[i];
	}
}
/**
* 广搜
*/
int bfs(int arr[N], int sHash, int tHash)
{
	//如果已知数等与目标
	if (sHash == tHash)
		return 0;
	int i, j;
	//定义一个队列
	queue<Node> q;
	//定义一个容器
	set<int> setHash;
	Node now, next;

	//以下几步是把一个结构体复制过去,及now=arr;
	{
		copyArray(arr, now.arr);
		//计算0的位置 
		int pos = 0;
		for (i = 0; i<N; i++)
		{
			if (arr[i] == 0)
				break;
			pos++;
		}
		now.hash = sHash;
		now.step = 0;
		now.pos = pos;
	}
	
	next.step = 0;
	q.push(now);
	setHash.insert(now.hash);
	while (!q.empty()){
		now = q.front();     //返回队列头部的元素给now
		q.pop();             //删除队列头部的元素
		for (i = 0; i<4; i++){
			cout << i << endl;
			int offsetX = 0, offsetY = 0;
			//顺时针旋转
			offsetX = (now.pos % 3 + dir[i][0]);
			offsetY = (now.pos / 3 + dir[i][1]);

			if (offsetX >= 0 && offsetX<3 && offsetY<3 && offsetY >= 0)
			{
				//每次换方向，就复制
				{
					copyArray(now.arr, next.arr);  
					next.step = now.step;
					next.step++;
					swap(next.arr, now.pos, offsetY * 3 + offsetX);
					next.hash = cantor(next.arr);
					next.pos = (offsetY * 3 + offsetX);
				}
				printArray(next.arr);

				int begin = setHash.size();
				setHash.insert(next.hash);
				int end = setHash.size();

				if (next.hash == tHash) {
					return next.step;
				}

				if (end>begin)
				{
					q.push(next);
				}
			}
		}
	}
	return -1;
}
/*
 *深搜
 */
int dfs(int arr[N], int sHash, int tHash)
{
	if (sHash == tHash) {
		return 0;
	}
 //这里应该是要用栈实现

}

/**
*求逆序数
*/
int inversion(int arr[N])
{
	int sum = 0;
	for (int i = 0; i<N; ++i)
	{
		for (int j = i + 1; j<N; ++j)
		{
			if (arr[j]<arr[i] && arr[j] != 0)//不与0比较  
			{
				sum++;
			}
		}
	}
	return sum;
}
int main()
{
	int i, j;
	string s = "283104765";
	string t = "123804765";
	int is[N], it[N]; //源int数组和目标int数组  
	for (i = 0; i<9; i++)
	{
		if (s.at(i) >= '0'&&s.at(i) <= '8')
		{
			is[i] = s.at(i) - '0';
		}
		else
		{
			is[i] = 0;
		}
		if (t.at(i) >= '0'&&t.at(i) <= '8')
		{
			it[i] = t.at(i) - '0';
		}
		else
		{
			it[i] = 0;
		}
	}
	cout << "打印初始8数码：" << endl;
	printArray(is);
	cout << "打印目标8数码：" << endl;
	printArray(it);

	int sHash, tHash;          //源哈希和目标哈希  

	sHash = cantor(is);
	tHash = cantor(it);
	int inver1 = inversion(is);//求初始格局的逆序数  
	int inver2 = inversion(it);//求目标格局的逆序数  
	if ((inver1 + inver2) % 2 == 0)
	{
		int step = bfs(is, sHash, tHash);
		cout << step << endl;
	}
	else
	{
		cout << "无法从初始状态到达目标状态" << endl;
	}
	system("pause");
	return 0;
}
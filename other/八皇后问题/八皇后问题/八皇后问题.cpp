// 八皇后问题.cpp: 定义控制台应用程序的入口点。
//递归算法问题

#include "stdafx.h"
#include<iostream>

using namespace std;
static int gEightQueen[8] = { 0 };    //八个皇后的位置
static int gCount = 0;                //排列方法


//输出每一种情况下棋盘中皇后的摆放情况
void print()
{
	for (int i = 0; i < 8; i++){
		
		int inner;
		for (int j = 0; j < gEightQueen[i]; j++)
			cout << "0";
		cout << "#";
		for (int j = gEightQueen[i] + 1; j < 8; j++)
			cout << "0";
		cout << endl;
	}
	cout << "==========================\n";
}

//检查是否存在有多个皇后在同一行/列/对角线的情况
int check_pos_valid(int n, int value)
{
	
	int data;
	for (int index = 0; index < n; index++)
	{
		data = gEightQueen[index];             //已确定的皇后的位置
		if (value == data)                     //同一列
			return 0;
		if ((index + data) == (n + value))     //同一行
			return 0;
		if ((index - data) == (n - value))     //对角线
			return 0;
	}
	return 1;
}
void eight_queen(int n)                         //n代表确定的皇后的数量
{

	for (int i = 0; i < 8; i++)
	{
		if (check_pos_valid(n, i))
		{
			gEightQueen[n] = i;                //确定每一种情况下每个皇后的位置
			if (7 == n)                
			{
				gCount++;
				print();
				gEightQueen[n] = 0;
				return;
			}
			eight_queen(n + 1);                 //递归,下一次寻找
			gEightQueen[n] = 0;
		}
	}
	cout << "wangkai";
}
int main()
{
	eight_queen(0);     //确定了0个
	cout << "total=" << gCount << endl;
	system("pause");
	return 0;
}
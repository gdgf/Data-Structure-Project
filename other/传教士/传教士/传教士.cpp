// 三个传教士问题.cpp: 定义控制台应用程序的入口点。
//以三元组存储(传教士，野人，是否到达岸边)，存储一个的人数(人数固定，所以只需要存储一个岸边的即可)

#include "stdafx.h"
#include <iostream> 
#include <vector>
#include <cmath>

using namespace std;
int X, Y;  //X为传教士 Y为野人
int k;     //k为船能搭载的人数
//三元组
struct node
{
	int q[3];
};
vector<node> s;
int q[500][3];
//用于存放搜索结点
//q[][0]是左岸传教士人数
//q[][1]是左岸野蛮人人数，q[][2]是左岸船的数目
//q[][3]用于搜索中的父亲结点序号。
int ans = 0;
int op_num = 0;     //可能的动作
int go[500][2];     //组合方式
int fx[500][500];   //组合方式构成的状态空间


//安全状态：左岸中，传教士都在or都不在or传教士人数等于野人人数 
int is_safe(int state[3])
{
	if ((state[0] == 0 || state[0] == X || state[0] == state[1]) && (state[1] >= 0) && (state[1] <= Y))
	{
		return 1;
	}
	return 0;
}

//是否到达目标状态 
int is_success(int state[3])
{
	if (state[0] == 0 && state[1] == 0)
		return 1;
	return 0;
}

//该状态是否已经访问过 记录访问节点
int vis(int state[3])
{
	for (vector<node>::iterator it = s.begin(); it != s.end(); it++)
		if ((*it).q[0] == state[0] && (*it).q[1] == state[1] && (*it).q[2] == state[2])
			return 1;
	return 0;
}

int f2(int state[3]) // A*算法
{
	return state[0] + state[1] - 2 * state[2];
}

int find_max(int cur)
{
	int max = -1;
	int op = -1;
	for (int j = 0; j < op_num; j++)     //分别考虑可能的动作
	{
		if (fx[cur + 1][j] > max)
		{
			max = fx[cur + 1][j];
			op = j;
		}
	}
	if (max == -1)
		op = -1;
	return op;
}

//过河操作
int search(int cur)
{
	if (is_success(q[cur]))
	{
		ans = cur;
		return 1;
	}
	int state[3];
	int j;

	if (q[cur][2])//船在左边
	{
		for (j = 0; j < op_num; j++)//分别考虑可能的动作
		{
			state[0] = q[cur][0] - go[j][0];
			state[1] = q[cur][1] - go[j][1];
			state[2] = 0;            //船到了右边
			fx[cur + 1][j] = f2(state);
		}
		j = find_max(cur);
		while (j != -1)
		{
			fx[cur + 1][j] = -1;
			state[0] = q[cur][0] - go[j][0];
			state[1] = q[cur][1] - go[j][1];
			state[2] = 0;   //船到了右边
			if (is_safe(state) && !vis(state))//如果是安全状态//判断与之前展开结点是否相同
			{
				node nd;
				nd.q[0] = q[cur + 1][0] = state[0];
				nd.q[1] = q[cur + 1][1] = state[1];
				nd.q[2] = q[cur + 1][2] = state[2];
				s.push_back(nd);
				//cout<<"合法结点:"<<state[0]<<' '<<state[1]<<' '<<state[2]<<endl;       
				if (search(cur + 1))
					return 1;
			}
			j = find_max(cur);
		}
	}
	else    //船在右边
	{
		for (j = 0; j < op_num; j++)//分别考虑可能的动作
		{
			state[0] = q[cur][0] + go[j][0];
			state[1] = q[cur][1] + go[j][1];
			state[2] = 1;
			fx[cur + 1][j] = f2(state);
		}
		j = find_max(cur);
		while (j != -1)
		{
			fx[cur + 1][j] = -1;
			state[0] = q[cur][0] + go[j][0];
			state[1] = q[cur][1] + go[j][1];
			state[2] = 1; //船回到左边
			if (is_safe(state) && !vis(state))//如果是安全状态且与之间状态不同
			{
				node nd;
				nd.q[0] = q[cur + 1][0] = state[0];
				nd.q[1] = q[cur + 1][1] = state[1];
				nd.q[2] = q[cur + 1][2] = state[2];
				s.push_back(nd);
				//cout<<"合法结点:"<<state[0]<<' '<<state[1]<<' '<<state[2]<<endl;
				if (search(cur + 1))
					return 1;
			}
			j = find_max(cur);
		}
	}
	return 0;
}

int main()
{
	int n;
	cout << "请输入野人和传教士的个数N：";
	cin >> n;
	cout << "请输入船能载的人数k：";
	cin >> k;
	X = Y = n;

	int state[3];
	//初始状态 
	node nd;
	nd.q[0] = state[0] = q[0][0] = X;
	nd.q[1] = state[1] = q[0][1] = Y;
	nd.q[2] = state[2] = q[0][2] = 1;

	s.push_back(nd);     //添加数据
	//初始化操作
	//合法的操作就是所有的百摆渡组合
	cout << "合法的操作组有：" << endl;
	for (int i = 1; i <= k; i++)
		for (int j = 0; j <= i; j++)
		{
			if (j >= i - j || j == 0)
			{
				go[op_num][0] = j;
				go[op_num][1] = i - j;
				cout << go[op_num][0] << ' ' << go[op_num][1] << endl;
				op_num++;
			}
		}
	cout <<"所有的组合方式总共有："<<op_num <<"种"<< endl;
	if (!search(0))
	{
		cout << "无解" << endl;
		return 0;
	}
	cout << "找到的解为:" << endl;
	for (int i = 0; i <= ans; i++)
	{
		//cout<<q[i][0]<<' '<<q[i][1]<<' '<<q[i][2]<<endl;
		if (i > 0)
		{
			cout << abs(q[i][0] - q[i - 1][0]) << "个传教士和" << abs(q[i][1] - q[i - 1][1]) << "个野人";
			if (q[i][2])
				cout << "从右岸乘船至左岸" << endl;
			else
				cout << "从左岸乘船至右岸" << endl;
			cout << "左岸有" << q[i][0] << "个传教士和" << q[i][1] << "个野人" << endl;
			cout << "右岸有" << n - q[i][0] << "个传教士和" << n - q[i][1] << "个野人" << endl << endl;
		}
	}

	cout << "本次搜索所花费的费用：" << ans << endl;
	system("pause");
	return 0;
}


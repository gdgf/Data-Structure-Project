// 汉诺塔问题.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
using namespace std;
int main()
{
	void move(int n, char a,char b, char c);
	
	int n;     //汉诺塔的层数
	while (1) {
		cout << "请输入汉诺塔的层数:" ;
		cin >> n;
		cout << "移动步骤为：" << endl;
		move(n, 'A', 'B', 'C');
	}
	cin.get();
    return 0;
}
void move(int n, char a, char b, char c) {
	if (n == 1) {
		cout << a << "->" << c << endl;
	}
	else {
		move(n - 1, a, c, b);
		cout<< a << "->" << c << endl;
		move(n - 1, b, a, c);
	}
}

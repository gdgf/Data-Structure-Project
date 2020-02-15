/*SetConsoleCursorPosition是一个计算机函数，
  如果用户定义了 COORD pos，那么pos其实是一个
  结构体变量，其中X和Y是它的成员，
  通过修改pos.X和pos.Y的值就可以实现光标的位置控制。
*/
#include<stdio.h>
#include<windows.h>
int main()
{
    HANDLE hOut;
    COORD pos={15,5};
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,pos);
    SetConsoleTextAttribute(hOut,0x01|0x05);
    printf("HelloWorld!\n");
    return 0;
}
/*
#include<stdio.h>
#include<windows.h>
int main()
{
    HANDLE hOut;
    COORD pos={0,0};
    int i;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut,0x01|0x05);
    for(i=0;i<20;i++){
        pos.X=i;
        pos.Y=i;
        SetConsoleCursorPosition(hOut,pos);
        printf("%d%d:HelloWorld!\n",pos.X,pos.Y);
        getchar();
    }
    return 0;
}
*/

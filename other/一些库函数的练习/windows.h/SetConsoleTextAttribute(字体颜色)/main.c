//�ο���ַ��https://baike.baidu.com/item/SetConsoleTextAttribute/570121?fr=aladdin
#include<stdio.h>
#include<windows.h>
int main(void)
{
    HANDLE consolehwnd;//�����������ϸ���֪ʶ����ٶ�һ�»��MSDN
    consolehwnd=GetStdHandle(STD_OUTPUT_HANDLE);//ʵ�������
    SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//����������ɫ

    printf("hello ");
    SetConsoleTextAttribute(consolehwnd,FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    printf("world!\n");
    getchar();
    SetConsoleTextAttribute(consolehwnd,BACKGROUND_INTENSITY|BACKGROUND_BLUE);
    printf("It is really beautiful!\n");
    return 0;
}

#include "graphics.h" //图形库
#include <time.h>     //设置随机数的种子
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<process.h>    //多线程

POINT point;           //windows自定义的结构体  点
HWND hwnd;             //窗口句柄
int sleeptime;         //函数挂起时间
//雨的链表节点结构体
typedef struct Rain
{
    int x0, y0;//雨滴的起始位置
    int x, y;//雨滴的终止位置
    double step;//步进
    COLORREF color;//雨滴的颜色
                   //雨滴的绘制所需的参数
    int left;
    int top;
    int right;
    int bottom;
    double stangle;
    double endangle;
    int n;
    Rain * next;
}Rain;
//雨滴入水声音
struct music
{
    int feq;
    int time;
    music* next;
    Rain *rain;
};
//闪电的结构体
typedef struct Thunder
{
    int x0, y0;//顶点位置
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int x4, y4;
    int x5, y5;
    int x6, y6;
    int x7, y7;
    int x8, y8;
    int x9, y9;
}Thunder;



//荷叶的结构体
typedef struct Lotus_Leaf
{
    int left;   //椭圆外切矩形的左上角 x 坐标。
    int top;   //椭圆外切矩形的左上角 y 坐标。
    int right;//椭圆外切矩形的右下角 x 坐标。
    int bottom;   //椭圆外切矩形的右下角 y 坐标。
    int x1, y1, x2, y2;   //横线1
    int x3, y3, x4, y4;   //横线2
    COLORREF fillcolor;
    COLORREF linecolor;
}Lotus_Leaf;


//池塘部分
void pool()
{
    IMAGE backpic;
    IMAGE qingwapic;
    //加载图片的池塘
    loadimage(&backpic, _T("chitang1.jpg"), 640, 480);
    loadimage(&qingwapic,_T("qingwa.gif"), 50, 50);
    putimage(0, 0, &backpic);//将背景图片放置在（0，0）处
    putimage(480, 300, &qingwapic);//将青蛙放置在（480，300）处
    //绘制池塘中的荷叶
    draw_leaf(450, 360, 550, 410, GREEN, BLACK);
    draw_leaf(380, 380, 480, 430, GREEN, BLACK);
}

//获得指定点的颜色
COLORREF Getcolor(int x, int y)
{
    //获得窗口句柄
    HDC hdc = GetImageHDC();
    return GetPixel(hdc, x + 20, y + 7);
}

//随机生成雨滴的位置和颜色
void InitRain(Rain *rain)
{
    rain->x0 = rand() % 640;//雨滴随机生成位置的确定
    rain->y0 = rand() % 200;
    rain->left = rain->x0;//绘制雨滴的参数的确定
    rain->top = rain->y0;
    rain->right = rain->x0 + 20;
    rain->bottom = rain->y0 + 35;
    rain->stangle = 4.28;
    rain->endangle = 5.22;
    rain->step = 40;//对雨滴动画实现所需的雨滴步进赋值
    int R = rand()%255; // 赋值随机数0~255；
    int G = rand()%255;
    int B = rand()%255;
    rain->color = RGB(R, G, B);//RGB函数 宏用于通过红、绿、蓝颜色分量合成颜色。
}


//形成雨滴的链表（循环列表）
void creatRain(Rain *ra)
{
    Rain *p, *q;
    int i;
    p = ra;
    for (i = 0; i < 40; i++)
    {
        q = (Rain *)malloc(sizeof(Rain));
        q->next = NULL;
        InitRain(q);
        p->next = q;
        p->n = i;
        p = q;
    }
    p->next = ra; //最后一个结点的next指向头结点
}

//计算雨线中雨滴的下一个位置
void rainMove(Rain *r)
{
    GetCursorPos(&point);   // 获取鼠标指针位置（屏幕坐标）
    ScreenToClient(hwnd, &point); // 将鼠标指针位置转换为窗口坐标
                                  //判断鼠标是否在窗口之内
    if (point.x >= 0 && point.x <= 640 && point.y >= 0 && point.y <= 480)
    {
        //雨滴的x随风而改变
//雨滴的y增大更多
        if (point.x >= 320)
        {
            r->x0 += 20;
            r->y0 += (r->step + 10);
        }
        else
        {
            r->x0 -= 20;
            r->y0 += (r->step + 10);
        }
        sleeptime = 130;//修改Sleep时间，加快雨滴(模拟狂风骤雨)
    }
    else
    {
        r->y0 = r->y0 + r->step;
        sleeptime = 250;//修改Sleep时间，减缓雨滴(模拟和风细雨)
    }

}
//檫除雨线中雨滴的上一个位置
void cleanRain(Rain *r)
{
    setfillcolor(Getcolor(r->x0, r->y0));//填充背景颜色(雨滴内)
    setlinecolor(Getcolor(r->x0, r->y0));//填充背景色(雨滴线)
    fillpie(r->x0, r->y0, r->x0 + 20, r->y0 + 25, r->stangle, r->endangle);//绘制雨滴
}

//绘制雨滴
void drowRain(Rain *r)
{
    setfillcolor(r->color);//填充随机颜色(雨滴内)
    setlinecolor(r->color);//填充随机颜色(雨滴线)
    fillpie(r->x0, r->y0, r->x0 + 20, r->y0 + 25, r->stangle, r->endangle);//绘制雨滴
}

//整个雨滴的动画效果
void rainDrop(Rain *r)
{
    if (r->y0 >= (300 + rand() % 180))
    {
        cleanrain(r);   //檫除雨滴
        r->x = r->x0;
        r->y = r->y0;
        m->rain = r;
        _beginthreadex(0, 0, (unsigned int(__stdcall *)(void *))drawwave,(music*)m, 0, 0);   //多线程
        InitRain(r);    //刷新雨滴
}
    else
    {
        cleanrain(r);//擦除雨滴
        rainmove(r);//计算雨滴下一个位置
        drowrain(r);//绘制雨滴
    }
}

void drawwave(Rain* r)
{
    int waveX, waveY;
    int R, G, B;
    //波纹大小随机
    waveX = rand() % 20 + 20;
    waveY = rand() % 10 + 10;
    //波纹颜色随机
    R = rand() % 255;
    G = rand() % 255;
    B = rand() % 255;
    Beep(2000, 100);
    setlinecolor(RGB(R, G, B));
    ellipse(r->x - waveX, r->y - waveY, r->x + waveX, r->y + waveY);
    setlinecolor(Getcolor(r->x, r->y));
    ellipse(r->x - waveX, r->y - waveY, r->x + waveX, r->y + waveY);
    Sleep(200);
    setlinecolor(RGB(R, G, B));
    ellipse(r->x - waveX - 20, r->y - waveY - 10, r->x + waveX + 20, r->y + waveY + 10);
    setlinecolor(Getcolor(r->x, r->y));
    ellipse(r->x - waveX - 20, r->y - waveY - 10, r->x + waveX + 20, r->y + waveY + 10);
    _endthread();
}

//荷叶部分
void draw_leaf(int left, int top, int right, int bottom, COLORREF fillcolor, COLORREF linecolor)
{
    //画荷叶的椭圆部分
    setfillcolor(fillcolor);
    setcolor(fillcolor);
    fillellipse(left, top, right, bottom);
    //画荷叶中的线条部分
    setlinecolor(linecolor);
    setlinestyle(PS_SOLID, 2);
    int ox = (left + right) / 2;
    int oy = (top + bottom) / 2;
    line(ox - 20, oy - 10, ox + 20, oy + 10);
    line(ox - 20, oy + 10, ox + 20, oy - 10);
    setlinecolor(linecolor);
}

void thunder()
{
    int x = rand() % 500;// +20;
    int y = rand() % 100;//+10;
    double stepx = rand() % 2;
    Thunder one;
    one.x0 = x + 0 * stepx; one.y0 = y + 0 * stepx;
    one.x1 = x + 188 * stepx; one.y1 = y + 125 * stepx;
    one.x2 = x + 103 * stepx; one.y2 = y + 138 * stepx;
    one.x3 = x + 134 * stepx; one.y3 = y + 187 * stepx;
    one.x4 = x + 90 * stepx; one.y4 = y + 193 * stepx;
    one.x5 = x + 121 * stepx; one.y5 = y + 271 * stepx;
    one.x6 = x + 33 * stepx; one.y6 = y + 168 * stepx;
    one.x7 = x + 72 * stepx; one.y7 = y + 163 * stepx;
    one.x8 = x + 30 * stepx; one.y8 = y + 112 * stepx;
    one.x9 = x + 85 * stepx; one.y9 = y + 105 * stepx;
    POINT thunder[] = {
        { one.x0,one.y0 },
        { one.x1,one.y1 },
        { one.x2,one.y2 },
        { one.x3,one.y3 },
        { one.x4,one.y4 },
        { one.x5,one.y5 },
        { one.x6,one.y6 },
        { one.x7,one.y7 },
        { one.x8,one.y8 },
        { one.x9,one.y9 },
    };
    setpolyfillmode(WINDING);
    setfillcolor(YELLOW);
    solidpolygon(thunder, 10);
    Sleep(200);
    clearpolygon(thunder, 10);
}

While（1）
{
    Beep（1000，500）；
}

music* getmusic()
{
    music*head = (music*)malloc(sizeof(music)),*temp=NULL,*m=NULL;
    m = head;
    m->feq = 1500;
    m->next = NULL;
    m->rain = NULL;
    m->time = 200;
    FILE* fp;
    errno_t err;
    err=fopen_s(&fp, "music.txt", "r");
    errno_t error=1;
    if(err)
    {
        system("cls");
        printf("音乐读取错误！\n");
        system("pause");
        head->next = head;
        return head;
    }
    else
    {
        while (error>0)
        {
            temp = (music*)malloc(sizeof(music));
            error=fscanf_s(fp, "%d %d\n", &temp->feq, &temp->time,8);
            temp->next = NULL;
            temp->rain = NULL;
            if (error > 0)
            {
                m->next = temp;
                m = temp;
            }
            else free(temp);
        }
        m->next = head;
        system("cls");
        printf("音乐读取成功！\n");
        system("pause");
        return head;
    }
}

//动画封装函数
void movie()
{
    music *mu=getmusic();
    //设置随机种子
    srand((unsigned)time(NULL));
    int i;
    //构造雨滴链表
    Rain *ra = (Rain *)malloc(sizeof(Rain));
    creatRain(ra);
    int thunder_time = 0;;
    // 创建绘图窗口
    initgraph(640, 480);
    setbkcolor(WHITE);
    while (1)
    {
        //绘制荷塘
        for (i = 0; i < 40;i++)
        {
            raindrop(ra,mu);
            ra = ra->next;
            mu = mu->next;
        }
        Sleep(sleeptime);
        pool();
        if (thunder_time % 30 == 1)
        {
        thunder();
            Beep(1000, 500);
        }
        thunder_time++;
        //_getch();
        //关闭绘图窗口

    }
    closegraph();
}
//... prompt'''

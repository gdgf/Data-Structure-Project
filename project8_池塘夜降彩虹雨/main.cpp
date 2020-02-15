#include "graphics.h" //ͼ�ο�
#include <time.h>     //���������������
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<process.h>    //���߳�

POINT point;           //windows�Զ���Ľṹ��  ��
HWND hwnd;             //���ھ��
int sleeptime;         //��������ʱ��
//�������ڵ�ṹ��
typedef struct Rain
{
    int x0, y0;//��ε���ʼλ��
    int x, y;//��ε���ֹλ��
    double step;//����
    COLORREF color;//��ε���ɫ
                   //��εĻ�������Ĳ���
    int left;
    int top;
    int right;
    int bottom;
    double stangle;
    double endangle;
    int n;
    Rain * next;
}Rain;
//�����ˮ����
struct music
{
    int feq;
    int time;
    music* next;
    Rain *rain;
};
//����Ľṹ��
typedef struct Thunder
{
    int x0, y0;//����λ��
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



//��Ҷ�Ľṹ��
typedef struct Lotus_Leaf
{
    int left;   //��Բ���о��ε����Ͻ� x ���ꡣ
    int top;   //��Բ���о��ε����Ͻ� y ���ꡣ
    int right;//��Բ���о��ε����½� x ���ꡣ
    int bottom;   //��Բ���о��ε����½� y ���ꡣ
    int x1, y1, x2, y2;   //����1
    int x3, y3, x4, y4;   //����2
    COLORREF fillcolor;
    COLORREF linecolor;
}Lotus_Leaf;


//��������
void pool()
{
    IMAGE backpic;
    IMAGE qingwapic;
    //����ͼƬ�ĳ���
    loadimage(&backpic, _T("chitang1.jpg"), 640, 480);
    loadimage(&qingwapic,_T("qingwa.gif"), 50, 50);
    putimage(0, 0, &backpic);//������ͼƬ�����ڣ�0��0����
    putimage(480, 300, &qingwapic);//�����ܷ����ڣ�480��300����
    //���Ƴ����еĺ�Ҷ
    draw_leaf(450, 360, 550, 410, GREEN, BLACK);
    draw_leaf(380, 380, 480, 430, GREEN, BLACK);
}

//���ָ�������ɫ
COLORREF Getcolor(int x, int y)
{
    //��ô��ھ��
    HDC hdc = GetImageHDC();
    return GetPixel(hdc, x + 20, y + 7);
}

//���������ε�λ�ú���ɫ
void InitRain(Rain *rain)
{
    rain->x0 = rand() % 640;//����������λ�õ�ȷ��
    rain->y0 = rand() % 200;
    rain->left = rain->x0;//������εĲ�����ȷ��
    rain->top = rain->y0;
    rain->right = rain->x0 + 20;
    rain->bottom = rain->y0 + 35;
    rain->stangle = 4.28;
    rain->endangle = 5.22;
    rain->step = 40;//����ζ���ʵ���������β�����ֵ
    int R = rand()%255; // ��ֵ�����0~255��
    int G = rand()%255;
    int B = rand()%255;
    rain->color = RGB(R, G, B);//RGB���� ������ͨ���졢�̡�����ɫ�����ϳ���ɫ��
}


//�γ���ε�����ѭ���б�
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
    p->next = ra; //���һ������nextָ��ͷ���
}

//������������ε���һ��λ��
void rainMove(Rain *r)
{
    GetCursorPos(&point);   // ��ȡ���ָ��λ�ã���Ļ���꣩
    ScreenToClient(hwnd, &point); // �����ָ��λ��ת��Ϊ��������
                                  //�ж�����Ƿ��ڴ���֮��
    if (point.x >= 0 && point.x <= 640 && point.y >= 0 && point.y <= 480)
    {
        //��ε�x�����ı�
//��ε�y�������
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
        sleeptime = 130;//�޸�Sleepʱ�䣬�ӿ����(ģ��������)
    }
    else
    {
        r->y0 = r->y0 + r->step;
        sleeptime = 250;//�޸�Sleepʱ�䣬�������(ģ��ͷ�ϸ��)
    }

}
//�߳���������ε���һ��λ��
void cleanRain(Rain *r)
{
    setfillcolor(Getcolor(r->x0, r->y0));//��䱳����ɫ(�����)
    setlinecolor(Getcolor(r->x0, r->y0));//��䱳��ɫ(�����)
    fillpie(r->x0, r->y0, r->x0 + 20, r->y0 + 25, r->stangle, r->endangle);//�������
}

//�������
void drowRain(Rain *r)
{
    setfillcolor(r->color);//��������ɫ(�����)
    setlinecolor(r->color);//��������ɫ(�����)
    fillpie(r->x0, r->y0, r->x0 + 20, r->y0 + 25, r->stangle, r->endangle);//�������
}

//������εĶ���Ч��
void rainDrop(Rain *r)
{
    if (r->y0 >= (300 + rand() % 180))
    {
        cleanrain(r);   //�߳����
        r->x = r->x0;
        r->y = r->y0;
        m->rain = r;
        _beginthreadex(0, 0, (unsigned int(__stdcall *)(void *))drawwave,(music*)m, 0, 0);   //���߳�
        InitRain(r);    //ˢ�����
}
    else
    {
        cleanrain(r);//�������
        rainmove(r);//���������һ��λ��
        drowrain(r);//�������
    }
}

void drawwave(Rain* r)
{
    int waveX, waveY;
    int R, G, B;
    //���ƴ�С���
    waveX = rand() % 20 + 20;
    waveY = rand() % 10 + 10;
    //������ɫ���
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

//��Ҷ����
void draw_leaf(int left, int top, int right, int bottom, COLORREF fillcolor, COLORREF linecolor)
{
    //����Ҷ����Բ����
    setfillcolor(fillcolor);
    setcolor(fillcolor);
    fillellipse(left, top, right, bottom);
    //����Ҷ�е���������
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

While��1��
{
    Beep��1000��500����
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
        printf("���ֶ�ȡ����\n");
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
        printf("���ֶ�ȡ�ɹ���\n");
        system("pause");
        return head;
    }
}

//������װ����
void movie()
{
    music *mu=getmusic();
    //�����������
    srand((unsigned)time(NULL));
    int i;
    //�����������
    Rain *ra = (Rain *)malloc(sizeof(Rain));
    creatRain(ra);
    int thunder_time = 0;;
    // ������ͼ����
    initgraph(640, 480);
    setbkcolor(WHITE);
    while (1)
    {
        //���ƺ���
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
        //�رջ�ͼ����

    }
    closegraph();
}
//... prompt'''

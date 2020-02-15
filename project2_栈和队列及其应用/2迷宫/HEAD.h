#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct point
{
	int x;
	int y;
	int m;  //通或不通
	int k;  //方向
}point;
typedef struct NodeType
{
    point data;
    struct NodeType *next,*roar;
}NodeType, *LinkType;

typedef struct
{
    LinkType top;
    LinkType base;
    int size;
}Stack;
point a[20][20];
void InitStack(Stack *s)
{
    s->base=(NodeType*)malloc(sizeof(NodeType));
    if (!s->base)
	{
		exit(0);
	}
	s->top=s->base;
	s->top->next=NULL;
	s->top->roar=NULL;
	s->size=0;
}
void DestroyStack(Stack *s)
{
    while(s->top!=s->base)
    {
        s->top=s->top->roar;
        free(s->top->next);
    }
    free(s->top);
}
int StackEmpty(Stack *s)
{
	if (s->top==s->base)
		return OK;
	else
		return ERROR;
}
Status GetTop(Stack *s,point *e)
{
    e->k=s->top->roar->data.k;
    e->m=s->top->roar->data.m;
    e->x=s->top->roar->data.x;
    e->y=s->top->roar->data.y;
    return OK;
}
Status push(Stack *s,point e)
{
    s->top->next=(NodeType*)malloc(sizeof(NodeType));
    if(!s->top->next) exit(0);
	s->top->data.k=e.k;
	s->top->data.m=e.m;
	s->top->data.x=e.x;
	s->top->data.y=e.y;
	s->size++;
	s->top->next->roar=s->top;
	s->top=s->top->next;
	s->top->next=NULL;
	return OK;
}
Status pop(Stack *s,point *e)
{
    if(s->top==s->base)
        return ERROR;
    e->k=s->top->roar->data.k;
    e->m=s->top->roar->data.m;
    e->x=s->top->roar->data.x;
    e->y=s->top->roar->data.y;
	s->top=s->top->roar;
	free(s->top->next);
	s->top->next=NULL;
	s->size--;
	return OK;
}
void build(int b,int c)
{
    int i,j;
    for(j=0;j<=c+1;j++)
    {
        a[0][j].m=1;
        a[0][j].x=0;
        a[0][j].y=j;
    }
    for(i=1;i<=b;i++)
    {
        a[i][0].m=1;
        a[i][0].x=i;
        a[i][0].y=0;
        for(j=1;j<=c;j++)
        {
            a[i][j].x=i;
            a[i][j].y=j;
            scanf("%d",&a[i][j].m);
        }
        a[i][c+1].m=1;
        a[i][c+1].x=i;
        a[i][c+1].y=c+1;
    }
    for(j=0;j<=c+1;j++)
    {
        a[b+1][j].m=1;
        a[b+1][j].x=b+1;
        a[b+1][j].y=j;
    }
}
void check(int t,int u,int v,int w,int row1,int col1)
//从设定的起点(t,u)到终点(v,w)寻找一条通路，若存在此通路将其压入栈中，并输出栈，即通路路径，输出“success”，并输出找到通路的迷宫，否则输出“FAIL”。
{
    Stack *s;
	point *r,f;
	NodeType *p;
	int pp,qq,end=0;
	s=(Stack*)malloc(sizeof(Stack));
	r=(point *)malloc(sizeof(point));
	if(a[t][u].m==1||a[v][w].m==1)//判断起点或终点是否不通。
    {
        printf("迷宫起点或终点不通，无解。\n");
        return;
    }
    InitStack(s);
    a[t][u].k=0; //初始化起点方向为0，不代表任何方向
    a[t][u].m=1;//起点值变为1
	push(s,a[t][u]);//起点入栈
	while (!StackEmpty(s))//栈不空则循环
	//若栈不空则循环判断下一坐标是否可行，直到找到一通路并输出；若栈空则说明无通路输出FAIL结束程序。
	{
		GetTop(s,r);
		if(r->x==v&&r->y==w)    //判断栈顶元素是否为终点，若是则输出通路结束程序。
		{
            end=1;
			p=s->base;
			do           //成功找到通路后从栈底到栈顶输出该通路，并将通路上的坐标改为2
            {
                a[p->data.x][p->data.y].m=2;
                printf("(%d,%d,%d)->",p->data.x,p->data.y,p->data.k);
                p=p->next;
            }
			while(p!=s->top);
			printf("Success\n");
		}
		if(a[r->x][r->y+1].m==0)   //判断坐标右侧是否可行，若可行则入栈，方向设为1
		{
			a[r->x][r->y+1].m=1; //颜色标记为深色1后入栈
			a[r->x][r->y].k=1;
			pop(s,&f);
			push(s,a[r->x][r->y]);
			push(s,a[r->x][r->y+1]);
		}
		else if(a[r->x+1][r->y].m==0)  //判断坐标下侧是否可行，若可行则入栈，方向设为2
		{
			a[r->x+1][r->y].m=1;
			a[r->x][r->y].k=2;
			pop(s,&f);
			push(s,a[r->x][r->y]);
			push(s,a[r->x+1][r->y]);
		}
		else if(a[r->x][r->y-1].m==0)  //判断坐标左侧是否可行，若可行则入栈，方向设为3
		{
			a[r->x][r->y-1].m=1;
			a[r->x][r->y].k=3;
			pop(s,&f);
			push(s,a[r->x][r->y]);
			push(s,a[r->x][r->y-1]);
		}
		else if(a[r->x-1][r->y].m==0) //判断坐标上侧是否可行，若可行则入栈，方向设为4
		{
			a[r->x-1][r->y].m=1;
			a[r->x][r->y].k=4;
			pop(s,&f);
			push(s,a[r->x][r->y]);
			push(s,a[r->x-1][r->y]);
		}
		else  //若坐标四个方向均不通则弹出栈顶元素并判断下一坐标
		{
		    pop(s,&f);
        }
	}
    if(end==0)
	{printf("Fail\n");}  //若无通路则输出FAIL
    for(pp=0;pp<=row1+1;pp++)   //以迷宫形式输出通路
    {
    for(qq=0;qq<=col1+1;qq++)
    {
        if(a[pp][qq].m==2)
            printf("* ");  //通路路径均以*表示
        else
        printf("1 ");
    }
        printf("\n");
    }
}

#endif // HEAD_H_INCLUDED


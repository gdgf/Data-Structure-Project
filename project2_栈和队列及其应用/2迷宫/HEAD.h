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
	int m;  //ͨ��ͨ
	int k;  //����
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
//���趨�����(t,u)���յ�(v,w)Ѱ��һ��ͨ·�������ڴ�ͨ·����ѹ��ջ�У������ջ����ͨ··���������success����������ҵ�ͨ·���Թ������������FAIL����
{
    Stack *s;
	point *r,f;
	NodeType *p;
	int pp,qq,end=0;
	s=(Stack*)malloc(sizeof(Stack));
	r=(point *)malloc(sizeof(point));
	if(a[t][u].m==1||a[v][w].m==1)//�ж������յ��Ƿ�ͨ��
    {
        printf("�Թ������յ㲻ͨ���޽⡣\n");
        return;
    }
    InitStack(s);
    a[t][u].k=0; //��ʼ����㷽��Ϊ0���������κη���
    a[t][u].m=1;//���ֵ��Ϊ1
	push(s,a[t][u]);//�����ջ
	while (!StackEmpty(s))//ջ������ѭ��
	//��ջ������ѭ���ж���һ�����Ƿ���У�ֱ���ҵ�һͨ·���������ջ����˵����ͨ·���FAIL��������
	{
		GetTop(s,r);
		if(r->x==v&&r->y==w)    //�ж�ջ��Ԫ���Ƿ�Ϊ�յ㣬���������ͨ·��������
		{
            end=1;
			p=s->base;
			do           //�ɹ��ҵ�ͨ·���ջ�׵�ջ�������ͨ·������ͨ·�ϵ������Ϊ2
            {
                a[p->data.x][p->data.y].m=2;
                printf("(%d,%d,%d)->",p->data.x,p->data.y,p->data.k);
                p=p->next;
            }
			while(p!=s->top);
			printf("Success\n");
		}
		if(a[r->x][r->y+1].m==0)   //�ж������Ҳ��Ƿ���У�����������ջ��������Ϊ1
		{
			a[r->x][r->y+1].m=1; //��ɫ���Ϊ��ɫ1����ջ
			a[r->x][r->y].k=1;
			pop(s,&f);
			push(s,a[r->x][r->y]);
			push(s,a[r->x][r->y+1]);
		}
		else if(a[r->x+1][r->y].m==0)  //�ж������²��Ƿ���У�����������ջ��������Ϊ2
		{
			a[r->x+1][r->y].m=1;
			a[r->x][r->y].k=2;
			pop(s,&f);
			push(s,a[r->x][r->y]);
			push(s,a[r->x+1][r->y]);
		}
		else if(a[r->x][r->y-1].m==0)  //�ж���������Ƿ���У�����������ջ��������Ϊ3
		{
			a[r->x][r->y-1].m=1;
			a[r->x][r->y].k=3;
			pop(s,&f);
			push(s,a[r->x][r->y]);
			push(s,a[r->x][r->y-1]);
		}
		else if(a[r->x-1][r->y].m==0) //�ж������ϲ��Ƿ���У�����������ջ��������Ϊ4
		{
			a[r->x-1][r->y].m=1;
			a[r->x][r->y].k=4;
			pop(s,&f);
			push(s,a[r->x][r->y]);
			push(s,a[r->x-1][r->y]);
		}
		else  //�������ĸ��������ͨ�򵯳�ջ��Ԫ�ز��ж���һ����
		{
		    pop(s,&f);
        }
	}
    if(end==0)
	{printf("Fail\n");}  //����ͨ·�����FAIL
    for(pp=0;pp<=row1+1;pp++)   //���Թ���ʽ���ͨ·
    {
    for(qq=0;qq<=col1+1;qq++)
    {
        if(a[pp][qq].m==2)
            printf("* ");  //ͨ··������*��ʾ
        else
        printf("1 ");
    }
        printf("\n");
    }
}

#endif // HEAD_H_INCLUDED


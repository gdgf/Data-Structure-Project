ADT的实现
1、【SeqList顺序表的ADT类型及实现】
/**
*次顺序表说明
*此顺序表为用数组存放的定长顺序表
*无论如何，顺序表一直存在，所以它的初始化和清空一样，都是将指定的length变为0；
*/
<抽象数据类型>
void InitList(SeqList *L);
/*将线性表初始化为空的线性表只需要把线性表的长度length置为0*/
int ListEmpty(SeqList L); 
/*判断线性表是否为空，线性表为空返回1，否则返回0*/
int GetElem(SeqList L,int i,DataType *e);   
/*查找线性表中第i个元素。查找成功将该值返回给e，并返回1表示成功；否则返回-1表示失败。*/
int LocateElem(SeqList L,DataType e);   
/*查找线性表中元素值为e的元素，查找成功将对应元素的序号返回，否则返回0表示失败。*/
int InsertList(SeqList *L,int i,DataType e);   
/*在顺序表的第i个位置插入元素e，插入成功返回1，如果插入位置不合法返回-1，顺序表满返回0*/
int DeleteList(SeqList *L,int i,DataType *e);
/*在顺序表的第i个位置删除元素，删除成功返回1，如果删除的位置不合法返回-1，顺序表空返回0*/
int ListLength(SeqList L);
/*返回顺序表的长度*/
void ClearList(SeqList *L);
/*清空顺序表*/
<实现>
//顺序表类型定义
#define ListSize 100
typedef int DataType;//定义元素类型为整型
typedef struct
{
	DataType list[ListSize];
	int length;
}SeqList;
void InitList(SeqList *L)    
//将线性表初始化为空的线性表只需要把线性表的长度length置为0
{
	L->length=0;	//把线性表的长度置为0
}
int ListEmpty(SeqList L)   
//判断线性表是否为空，线性表为空返回1，否则返回0
{
    if(L.length==0)			//判断线性表的长度是否为0
        return 1;			//当线性表为空时，返回1；否则返回0
    else
        return 0;
}
int GetElem(SeqList L,int i,DataType *e)   
//查找线性表中第i个元素。查找成功将该值返回给e，并返回1表示成功；否则返回-1表示失败。
{
	if(i<1||i>L.length)  	//在查找第i个元素之前，判断该序号是否合法
        return -1;
	*e=L.list[i-1];			//将第i个元素的值赋值给e
    return 1;
}
int LocateElem(SeqList L,DataType e)   
//查找线性表中元素值为e的元素，查找成功将对应元素的序号返回，否则返回0表示失败。
{
    int i;
	for(i=0;i<L.length;i++)	 //从第一个元素开始比较
        if(L.list[i]==e)
			return i+1;
		return 0;
}
int InsertList(SeqList *L,int i,DataType e)   
//在顺序表的第i个位置插入元素e，插入成功返回1，如果插入位置不合法返回-1，顺序表满返回0
{
    int j;
	if(i<1||i>L->length+1)				//在插入元素前，判断插入位置是否合法
	{
        printf("插入位置%d不合法！\n",i);
        return -1;
	}
	else if(L->length>=ListSize)		//在插入元素前，判断顺序表是否已经满，不能插入元素
	{
		printf("顺序表已满，不能插入元素。\n");
		return 0;
	}
	else
	{
		for(j=L->length;j>=i;j--)			//将第i个位置以后的元素依次后移
			L->list[j]=L->list[j-1];
        L->list[i-1]=e;			          //插入元素到第i个位置
        L->length=L->length+1;	          //将顺序表长增1
        return 1;
	}
}
int DeleteList(SeqList *L,int i,DataType *e)
//在顺序表的第i个位置删除元素，删除成功返回1，如果删除的位置不合法返回-1，顺序表空返回0
{
    int j;
    if(L->length<=0)
    {
        printf("顺序表已空不能进行删除!\n");
        return 0;
    }
    else if(i<1||i>L->length)
    {
        printf("删除位置不合适!\n");
        return -1;
    }
    else
    {
        *e=L->list[i-1];
        for(j=i;j<=L->length-1;j++)
            L->list[j-1]=L->list[j];
        L->length=L->length-1;
        return 1;
    }
}
int ListLength(SeqList L)
//返回顺序表的长度
{
    return L.length;
}
void ClearList(SeqList *L)
//清空顺序表
{
	L->length=0;
}
2、【LinkList线性单链表的ADT类型及实现】
<抽象数据类型>
void InitList(LinkList *h);
//单链表的初始化
int ListEmpty(LinkList h);
//判断单链表是否为空
ListNode *Get(LinkList h,int i);
//找单链表中第i个结点。查找成功返回该结点的指针，否则返回NULL
ListNode *LocateElem(LinkList h,DataType e);
//查找线性表中元素值为e的元素,查找成功返回对应元素的结点指针，否则返回NULL
int LocatePos(LinkList h,DataType e);
//查找线性表中元素值为e的元素，查找成功返回对应元素的序号，否则返回0
int InsertList(LinkList h,int i,DataType e);
//在单链表中第i个位置插入值e的结点。插入成功返回1，失败返回0
int DeleteList(LinkList h,int i,DataType *e);
//删除单链表中的第i个位置的结点。删除成功返回1，失败返回0
int ListLength(LinkList h);
//求线性表的表长
void DestroyList(LinkList h)
//销毁链表
<实现>
//数据类型
typedef int DataType;
typedef struct Node
{
    DataType data;
    struct Node *next;
}ListNode,*LinkList;    //ListNode是链表的结点类型，LinkList是指向链表结点的指针类型。 

//线性链表的基本操作
void InitList(LinkList *h)
//单链表的初始化
{
    if((*h=(LinkList)malloc(sizeof(ListNode)))==NULL)   //为头结点分配一个存储空间
        exit(-1);
    (*h)->next=NULL;			//将单链表的头结点指针域置为空
}
int ListEmpty(LinkList h)
//判断单链表是否为空
{
    if(h->next==NULL)			//如果链表为空
        return 1;				//返回1
    else						//否则
        return 0; 				//返回0
}
ListNode *Get(LinkList h,int i)
/*
查找一个结点存在与否需要考虑的问题
(1)、链表是否为空
(2)、寻找位置是否合法
 */
//找单链表中第i个结点。查找成功返回该结点的指针，否则返回NULL
{
    ListNode *p;
    int j;

    if(ListEmpty(h))		//查找第i个元素之前，判断链表是否为空
        return NULL;
    if(i<1)				   //判断该序号是否合法
       return NULL;
    j=0;
    p=h;                 //p指向头结点
    //目的是获得第i个元素的地址
    while(p->next!=NULL&&j<i)
    {
        p=p->next;
        j++;
    }
    if(j==i) 			//如果找到第i个结点
        return p;		//返回指针p
    else    			//否则
        return NULL	;   //返回NULL
    }
ListNode *LocateElem(LinkList h,DataType e)
//查找线性表中元素值为e的元素,查找成功返回对应元素的结点指针，否则返回NULL
{
    ListNode *p;
    p=h->next;		    //指针p指向第一个结点
    while(p)
    {
        if(p->data!=e)	//如果当前元素值与e不相等
            p=p->next; 	//则继续查找
        else			//否则
            break; 		//退出循环，停止查找
    }
    return p; 			//返回结点的指针
}
int LocatePos(LinkList h,DataType e)
//查找线性表中元素值为e的元素，查找成功返回对应元素的序号，否则返回0
{
    ListNode *p;
    int i;
    if(ListEmpty(h))    //查找第i个元素之前，判断链表是否为空
        return NULL;
    p=h->next;		    //从第一个结点开始查找
    i=1;
    while(p)            //当p!=NULL时
    {
        if(p->data==e)	//找到与e相等的元素
            return i; 	//返回该序号
        else			//否则
        {
            p=p->next;  //继续查找
            i++;
        }
    }
    if(!p)				//如果没有找到与e相等的元素，返回0，表示失败
        return 0;
    }
int InsertList(LinkList h,int i,DataType e)
//在单链表中第i个位置插入值e的结点。插入成功返回1，失败返回0
{
    ListNode *p,*pre;
    int j;
    pre=h;			   //指针pre指向头结点
    j=0;
    while(pre->next!=NULL&&j<i-1)//找到第i-1个结点，即第i个结点的前驱结点
    {
        pre=pre->next;
        j++;
    }
    if(j!=i-1)			//如果没找到，说明插入位置错误
    {
        printf("插入位置错");
        return 0;
    }
    //新生成一个结点，并将e赋值给该结点的数据域
    if((p=(ListNode*)malloc(sizeof(ListNode)))==NULL)
        exit(-1);
    p->data=e;
    //插入结点操作
    p->next=pre->next;
    pre->next=p;
    return 1;
}
int DeleteList(LinkList h,int i,DataType *e)
/*
删除第i个结点需要考虑的问题：
（1）、先查找i个结点的前一个结点
（2）、判断删除位置i是否正确
（3）、连接
*/
//删除单链表中的第i个位置的结点。删除成功返回1，失败返回0
{
    ListNode *pre,*p;
    int j;
    pre=h;
    j=0;
    //寻找前一个的位置
    while(pre->next!=NULL&&pre->next->next!=NULL&&j<i-1)
	//pre->next!=NULL：链表不为空;pre->next->next!=NULL: 保证被删除元素在链表内;j<i-1:找到指向第i-1个结点的指针                      
    {
        pre=pre->next;
        j++;
    }
    if(j!=i-1)				//如果没找到要删除的结点位置，说明删除位置错误
    {
        printf("删除位置错误");
        return 0;
    }
    p=pre->next;            //要删除的结点
    *e=p->data;             
    pre->next=p->next;
    free(p);				
    return 1;
}
int ListLength(LinkList h)
//求线性表的表长
{
    ListNode *p;
    int count=0;      //计数器
    p=h;
    while(p->next!=NULL)
    {
        p=p->next;
        count++;
    }
    return count;
}
void DestroyList(LinkList h)
//销毁链表
{
    ListNode *p,*q;
    p=h;
    while(p!=NULL)
   {
        q=p;
        p=p->next;
        free(q);
    }
}
3、【SLinkList静态链表的ADT类型及实现】
<抽象数据类型>
void InitSList(SLinkList *L);
//静态链表初始化
int AssignNode(SLinkList L);
//分配结点
void FreeNode(SLinkList L,int pos);
//结点的回收
void InsertSList(SLinkList *L,int i,DataType e);
//插入操作
void DeleteSList(SLinkList *L,int i,DataType*e);
//删除操作
void PrintDList(SLinkList L,int n);
//输出静态链表中的所有元素
<实现>
-----数据类型------
typedef int DataType;
#define ListSize 100
typedef struct{
    DataType data;
    int cur;              //       
}SListNode;               //SListNode是一个结点类型
typedef struct
{
	SListNode list[ListSize];
	int av;              // av是备用链表的指针，
}SLinkList;              //SLinkList是一个静态链表类型

void InitSList(SLinkList *L)
//静态链表初始化
{
    int i;
    for(i=0;i<ListSize;i++)
      (*L).list[i].cur=i+1;
    (*L).list[ListSize-1].cur=0;
    (*L).av=1;
}
int AssignNode(SLinkList L)
//从备用链表中取下一个结点空间，分配给要插入链表中的元素，并返回要插入结点的位置
//即让备用指针下移一个单位。
{
    int i;
    i=L.av;
    L.av=L.list[i].cur;
    return i;
}
void FreeNode(SLinkList L,int pos)
//结点的回收
{
    L.list[pos].cur=L.av;
    L.av=pos;
}
void InsertSList(SLinkList *L,int i,DataType e)
//插入操作
{
    int j,k,x;

    k=(*L).av;                   //从备用链表中取出一个空闲结点
    (*L).av=(*L).list[k].cur;    //使备用链表指向下一个有用结点
    (*L).list[k].data=e;         //把新元素放进新结点中    
    j=(*L).list[0].cur;
    for(x=1;x<i-1;x++)
       j=(*L).list[j].cur;       //找到插入位置前一位的cur 
    (*L).list[k].cur=(*L).list[j].cur;
    (*L).list[j].cur=k;
}
void DeleteSList(SLinkList *L,int i,DataType*e)
//删除操作
{
    int j,k,x;
    j=(*L).list[0].cur;
    for(x=1;x<i-1;x++) 
      j=(*L).list[j].cur;          //找到要删除位置前一位的cur     
    k=(*L).list[j].cur;            //删除位置
    (*L).list[j].cur=(*L).list[k].cur;
    (*L).list[k].cur=(*L).av;      //收入备用结点
    *e=(*L).list[k].data;
    (*L).av=k;
}
void PrintDList(SLinkList L,int n)
/*输出静态链表中的所有元素*/
{
	int j,k;
	k=L.list[0].cur;
	for(j=1;j<=n;j++)
	{
		printf("%4d",L.list[k].data);
		k=L.list[k].cur;
	}
	printf("\n");
}
4、【SeqStack顺序栈的ADT类型及实现】
<抽象数据类型>
void InitStack(SeqStack *S);
/*栈的初始化*/
int StackEmpty(SeqStack S);   
/*判断栈是否为空，栈为空返回1，否则返回0*/
int GetTop(SeqStack S, DataType *e);   
/*取栈顶元素。将栈顶元素值返回给e*/
int PushStack(SeqStack *S,DataType e);   
/*将元素e进栈，元素进栈成功返回1，否则返回0.*/
int PopStack(SeqStack *S,DataType *e);
/*出栈操作。将栈顶元素出栈，并将其赋值给e。出栈成功返回1，否则返回0*/
int StackLength(SeqStack S);
/*求栈的长度*/
void ClearStack(SeqStack *S);    
/*清空栈*/

<实现>
#define StackSize 100
typedef struct
{
    DataType stack[StackSize];
    int top;        //栈顶指针
}SeqStack;

void InitStack(SeqStack *S)    
//栈的初始化
{
   S->top=0;	//把栈顶指针置为0
}
int StackEmpty(SeqStack S)   
//判断栈是否为空，栈为空返回1，否则返回0
{
    if(S.top==0)			//当栈顶指针top为0
        return 1;			//返回
    else					//否则
        return 0; 			//返回0
}
int GetTop(SeqStack S, DataType *e)   
//取栈顶元素。将栈顶元素值返回给e
{
   if(S.top<=0)		//取栈顶元素前，判断栈是否为空
   {
     printf("栈已经空!\n");
     return 0;
   }
	else
	{
		*e=S.stack[S.top-1];	//在取栈顶元素
		return 1;
	}
}
int PushStack(SeqStack *S,DataType e)   
//将元素e进栈，元素进栈成功返回1，否则返回0.
{
	if(S->top>=StackSize)				//元素进栈前，判断是否栈已经满
	{
		printf("栈已满，不能进栈！\n");
		return 0;
	}
	else
	{
		S->stack[S->top]=e;			//元素e进栈
		S->top++;					//修改栈顶指针
		return 1;
	}
}
int PopStack(SeqStack *S,DataType *e)
//出栈操作。将栈顶元素出栈，并将其赋值给e。出栈成功返回1，否则返回0
{
    if(S->top==0)		//元素出栈之前，判断栈是否为空
    {
        printf("栈已经没有元素，不能出栈!\n");
        return 0;
    }
    else
    {
		S->top--;			        //先修改栈顶指针
		*e=S->stack[S->top];	    //将出栈元素赋值给e
	    return 1;
    }
}
int StackLength(SeqStack S)
/*求栈的长度*/
{
    return S.top;
}
void ClearStack(SeqStack *S)    
/*清空栈*/
{
    S->top=0;			/*将栈顶指针置为0*/
}
5、【SSeqStack顺序栈的ADT类型及实现】
#define STACKSIZE 100
typedef struct
{
    DataType stack[STACKSIZE];
    int top[2];
}SSeqStack;
void InitStack(SSeqStack *S)
/*共享栈的初始化操作*/
{
    S->top[0]=0;
    S->top[1]=STACKSIZE-1;
}
int PushStack(SSeqStack *S,DataType e,int flag)
/*共享栈进栈操作。进栈成功返回1，否则返回0*/
{
if(S->top[0]==S->top[1])		/*在进栈操作之前，判断共享栈是否已满*/
    return 0;
switch(flag)
{
    case 1:				/*当flag为0，表示元素要进左端的栈*/
        S->stack[S->top[0]]=e;	/*元素进栈*/
        S->top[0]++;			/*修改栈顶指针*/
        break;
    case 2:				/*当flag为1，表示元素要进右端的栈*/
        S->stack[S->top[1]]=e;	/*元素进栈*/
        S->top[1]--;			/*修改栈顶指针*/
        break;
    default:
        return 0;
}
return 1;
}
int PopStack(SSeqStack *S,DataType *e,int flag)
{
	switch(flag) 			/*在出栈操作之前，判断是哪个栈要进行出栈操作*/
	{
		case 1:
			if(S->top[0]==0)	/*左端的栈为空，则返回0，表示出栈操作失败*/
				return 0;
			S->top[0]--;		/*修改栈顶指针*/
			*e=S->stack[S->top[0]];	/*将出栈的元素赋值给e*/
			break;
		case 2:
			if(S->top[1]==STACKSIZE-1)	/*右端的栈为空，则返回0，表示出栈操作失败*/
				return 0;
			S->top[1]++;				/*修改栈顶指针*/
			*e=S->stack[S->top[1]];	/*将出栈的元素赋值给e*/
			break;
		default:
			return 0;
}
return 1;
}
int StackEmpty(SSeqStack S,int flag)
/*判断栈是否为空。如果栈为空，返回1；否则，返回0。*/
{
	switch(flag)
	{
	case 1: 		/*为1，表示判断左端的栈是否为空*/
		if(S.top[0]==0)
			return 1;
		break;
	case 2: 		/*为2，表示判断右端的栈是否为空*/
		if(S.top[1]==STACKSIZE-1)
			return 1;
		break;
	default:
        printf("输入的flag参数错误!");
		return -1;			
	}
	return 0;
}
int GetTop(SSeqStack S, DataType *e,int flag)   
/*取栈顶元素。将栈顶元素值返回给e，并返回1表示成功；否则返回0表示失败。*/
{
	switch(flag)
	{
	case 1:		 /*为1，表示要取左端栈的栈顶元素*/
		if(S.top[0]==0)
			return 0;
		*e=S.stack[S.top[0]-1];
		break;
	case 2: 		/*为2，表示要取右端栈的栈顶元素*/
		if(S.top[1]==STACKSIZE-1)
			return 0;
		*e=S.stack[S.top[1]+1];
		break;
	default:
		return 0;			
	}
	return 1;
}
6、【LinkStack链栈的ADT类型及实现】
<抽象数据类型>
void InitStack(LinkStack *top);
/*初始化链式栈。为头结点动态申请一块内存空间，并将指针域置为NULL*/
int StackEmpty(LinkStack top)
/*判断链式栈是否为空。如果链式栈为空，则返回1；否则，返回0*/
int PushStack(LinkStack top,DataType e);
/*入栈操作。如果入栈操作成功，返回1*/
int PushStack(LinkStack top,DataType e);
/*入栈操作。如果入栈操作成功，返回1*/
int PopStack(LinkStack top,DataType *e);
/*出栈操作。出栈操作成功返回1，否则返回0*/
int StackLength(LinkStack top);
/*求栈的长度*/
void ClearStack(LinkStack top);
/*清空栈。释放链式栈中的每一个结点所占的内存空间*/
<实现》
typedef struct node
{
	DataType data;
	struct node *next;
}LinkStackNode,*LinkStack;

void InitStack(LinkStack *top)
/*初始化链式栈。为头结点动态申请一块内存空间，并将指针域置为NULL*/
{
	if((*top=(LinkStackNode*)malloc(sizeof(LinkStackNode)))==NULL)
	{
		printf("分配结点失败！\n");
		exit(-1);
	}
	(*top)->next=NULL;
}
int StackEmpty(LinkStack top)
/*判断链式栈是否为空。如果链式栈为空，则返回1；否则，返回0*/
{
	if(top->next==NULL)		/*如果头结点的指针域为空*/
		return 1; 			/*则返回1*/
	else					/*如果头结点的指针域不为空*/
		return 0; 			/*则返回0*/
}
int GetTop(LinkStack top,DataType *e)
/*取栈顶元素。如果取栈顶元素成功返回1，否则返回0*/
{
	LinkStackNode *p;
	p=top->next;			/*p指向栈顶结点*/
	if(!p) 					/*如果栈不为空*/
	{
		printf("栈已空，不能取栈顶元素！\n");
		return 0; 			/*返回0表示取栈顶元素失败*/
	}
	*e=p->data; 			/*取出栈顶元素赋值给e*/
	return 1; 				/*返回1表示取栈顶元素成功*/
}
int PushStack(LinkStack top,DataType e)
/*入栈操作。如果入栈操作成功，返回1*/
{
	LinkStackNode *p;
	if((p=(LinkStackNode*)malloc(sizeof(LinkStackNode)))==NULL)	/*动态生成一个新结点*/
	{
		printf("内存分配失败！\n");
		exit(-1);
	}
	p->data=e; 				/*将元素值e存放到新结点数据域*/
	p->next=top->next; 		/*新结点指向原来的栈顶*/
	top->next=p; 			/*新结点成为栈顶*/
	return 1; 				/*返回1表示入栈操作成功*/
}
int PopStack(LinkStack top,DataType *e)
/*出栈操作。出栈操作成功返回1，否则返回0*/
{
	LinkStackNode *p;
	p=top->next; 			/*p指向栈顶结点*/
	if(!p) 					/*如果栈为空*/
	{
		printf("栈为空，不能进行出栈操作！\n");
		return 0; 			/*返回0表示出栈操作失败*/
	}
	top->next=p->next; 		/*删除栈顶结点*/
	free(p); 				/*释放结点所占内存空间*/
	return 1; 				/*返回1表示出栈操作成功*/
}
int StackLength(LinkStack top)
/*求栈的长度*/
{
	int n=0;				/*n用作计数器*/
	LinkStackNode *p;
	p=top; 				/*从栈顶指针开始*/
	while(p->next!=NULL) 	/*如果栈不为空*/
	{
		p=p->next; 			/*访问下一个结点*/
		n++;				/*计数器加1*/
	}
	return n; 				/*返回栈的长度*/
}
void ClearStack(LinkStack top)
/*清空栈。释放链式栈中的每一个结点所占的内存空间*/
{
	LinkStackNode *p,*q;
	p=top; 			/*从栈顶指针开始*/
	while(!p) 			/*如果栈不为空*/
	{
		q=p; 			/*q指向要释放的结点*/
		p=p->next; 		/*p指向下一个结点*/
		free(q); 		/*释放结点*/
	}
}
7、【SeqQueue顺序队列的ADT类型及实现】
#define QueueSize 100
typedef struct Squeue{	/*顺序队列类型定义*/
	DataType queue[QueueSize];
	int front,rear;	/*队头指针和队尾指针*/
}SeqQueue;
void InitQueue(SeqQueue *SQ)    
/*将顺序队列初始化为空队列只需要把队头指针和队尾指针同时置为0*/
{
    SQ->front=SQ->rear=0;	/*把队头指针和队尾指针同时置为0*/
}
int QueueEmpty(SeqQueue SQ)   
/*判断队列是否为空，队列为空返回1，否则返回0*/
{
   if(SQ.front==SQ.rear)		/*判断队头指针和队尾指针是否相等*/
       return 1;			/*当队列为空时，返回1；否则返回0*/
   else
       return 0;
}
int EnQueue(SeqQueue *SQ,DataType x)   
/*将元素x插入到顺序队列SQ中，插入成功返回1，否则返回0*/
{
   if(SQ->rear==QueueSize)  	/*在插入新的元素之前，判断队尾指针是否到达数组的最大值，即是否队列已满*/
       return 0;
   SQ->queue[SQ->rear]=x;	/*在队尾插入元素x */
   SQ->rear=SQ->rear+1;    	/*队尾指针向后移动一个位置*/
   return 1;
}
int DeQueue(SeqQueue *SQ,DataType *e)
/*删除顺序队列中的队头元素，并将该元素赋值给e，删除成功返回1，否则返回0*/
{
   if(SQ->front==SQ->rear)  /*在删除元素之前，判断队列是否为空*/
       return 0;
   else
   {
      *e=SQ->queue[SQ->front]; 	/*将要删除的元素赋值给e*/
       SQ->front=SQ->front+1;	/*将队头指针向后移动一个位置，指向新的队头*/
       return 1;
   }
}

int GetHead (SeqQueue SCQ,DataType *e)
/*取队头元素，并将该元素赋值给e，取元素成功返回1，否则返回0*/
{
	if(SCQ.front==SCQ.rear)		/*在取队头元素之前，判断顺序循环队列是否为空*/
	   return 0;
	else
	{
	    *e=SCQ.queue[SCQ.front];	/*将队头元素赋值给e，取出队头元素*/
	    return 1;
	}
}

8、【LinkQueue链式队列的ADT类型及实现】
typedef char DataType;	/*数据类型为字符类型*/
/*链式堆栈结点类型定义*/
typedef struct snode
{
	DataType data;
	struct snode *next;
}LSNode;
/*只有队尾指针的链式循环队列类型定义*/
typedef struct QNode
{
	DataType data;
	struct QNode *next;
}LQNode,*LinkQueue;

void InitStack(LSNode **head)
/*带头结点的链式堆栈初始化*/
{
	if((*head=(LSNode*)malloc(sizeof(LSNode)))==NULL)/*为头结点分配空间*/
	{
		printf("分配结点不成功");
		exit(-1);
	}
	else
		(*head)->next=NULL;			/*头结点的指针域设置为空*/
}
int StackEmpty(LSNode *head)
/*判断带头结点链式堆栈是否为空。如果堆栈为空，返回1，否则返回0*/
{
	if(head->next==NULL)	/*如果堆栈为空，返回1，否则返回0*/
		return 1;
	else
		return 0;
}
int PushStack(LSNode *head,DataType e)
/*链式堆栈进栈。进栈成功返回1，否则退出*/
{
	LSNode *s;
	if((s=(LSNode*)malloc(sizeof(LSNode)))==NULL)/*为结点分配空间，失败退出程序并返回-1*/
		exit(-1);
	else
	{
		s->data=e;				/*把元素值赋值给结点的数据域*/
		s->next=head->next;		/*将结点插入到栈顶*/
		head->next=s;
		return 1;
	}
}
int PopStack(LSNode *head,DataType *e)
/*链式堆栈出栈，需要判断堆栈是否为空。出栈成功返回1，否则返回0*/
{
	LSNode *s=head->next;		/*指针s指向栈顶结点*/
	if(StackEmpty(head))		/*判断堆栈是否为空*/
		return 0;
	else
	{
		head->next=s->next;		/*头结点的指针指向第二个结点位置*/
		*e=s->data;				/*要出栈的结点元素赋值给e*/
		free(s);				/*释放要出栈的结点空间*/
		return 1;	
	}
}
void InitQueue(LinkQueue *rear)   
/*将带头结点的链式循环队列初始化为空队列，需要把头结点的指针指向头结点*/
{
	if((*rear=(LQNode*)malloc(sizeof(LQNode)))==NULL)
		exit(-1);					/*如果申请结点空间失败退出*/
	else
		(*rear)->next=*rear;		/*队尾指针指向头结点*/
}

int QueueEmpty(LinkQueue rear)    
/*判断链式队列是否为空，队列为空返回1，否则返回0*/
{
	if(rear->next==rear)		/*判断队列是否为空。当队列为空时，返回1，否则返回0*/
        return 1;
    else
        return 0;
}

int EnQueue(LinkQueue *rear,DataType e)
/*将元素e插入到链式队列中，插入成功返回1*/
{
    LQNode *s;
	s=(LQNode*)malloc(sizeof(LQNode));	/*为将要入队的元素申请一个结点的空间*/
	if(!s) exit(-1);					/*如果申请空间失败，则退出并返回参数-1*/
	s->data=e;							/*将元素值赋值给结点的数据域*/
	s->next=(*rear)->next;				/*将新结点插入链式队列*/
	(*rear)->next=s;
	*rear=s;							/*修改队尾指针*/
    return 1;
}
int DeQueue(LinkQueue *rear,DataType *e)
/*删除链式队列中的队头元素，并将该元素赋值给e，删除成功返回1，否则返回0*/
{
	LQNode *f,*p;
	if(*rear==(*rear)->next)	/*在删除队头元素即出队列之前，判断链式队列是否为空*/
        return 0;
    else
	{
		f=(*rear)->next;		/*使指针f指向头结点*/
		p=f->next;				/*使指针p指向要删除的结点*/	
		if(p==*rear)			/*处理队列中只有一个结点的情况*/
		{
			*rear=(*rear)->next;/*使指针rear指向头结点*/
			(*rear)->next=*rear;
		}
		else
			f->next=p->next;	/*使头结点指向要出队列的下一个结点*/
		*e=p->data;				/*把队头元素值赋值给e*/
		free(p);				/*释放指针p指向的结点*/
        return 1; 
    }
}
9.【SeqString.h实现】
		void CreateString(SeqString *s,char str[])
		{
			strcpy(s->str,str);
			s->length=strlen(str);
		}
		 void StrAssign(SeqString *S,char cstr[]) 
			/*串的赋值操作*/
		   {
				 int i=0;
				 for(i=0;cstr[i]!=’\0’;i++)	/*将常量cstr中的字符赋值给串S*/
					S->str[i]=cstr[i];
				 S->length=i;
			 }
          int StrEmpty(SeqString S)   
		/*判断串是否为空，串为空返回1，否则返回0*/
		{
			if(S.length==0)			/*如果串的长度等于0*/
				return 1;			/*返回1*/
			else                    /*否则*/
				return 0;            /*返回0*/
		}
        //求串的长度。
		int StrLength(SeqString S) 
		{
			  return S.length;
		}
		//串的复制。
		void StrCopy(SeqString *T,SeqString S) 
		{
			  int i;
			  for(i=0;i<S.length;i++)		/*将串S的字符赋值给串T*/
				   T->str[i]=S.str[i];
			  T->length=S.length; 		/*将串S的长度赋值给串T*/
		}
        int StrCompare(SeqString S,SeqString T)
	   /*串的比较操作*/
	   {
			int i;
			for(i=0;i<S.length&&i<T.length;i++)	/*从第一个字符开始比较两个串中的字符*/
				 if(S.str[i]!=T.str[i]) 	/*如果有不相等的字符*/
					  return (S.str[i]-T.str[i]);      /*返回两个字符的差值*/
			return (S.length-T.length); 			/*如果比较完毕，返回两个串的长度的差值*/
		}
        //删除串S中pos开始的len个字符。
		int StrDelete(SeqString *S,int pos,int len)
		{
			 int i;
			 if(pos<0||len<0||pos+len-1>S->length)/*如果参数不合法，则返回0*/
				{
					  printf(“删除位置不正确，参数len不合法”);
					  return 0;
				 }
			 else
			{
				  for(i=pos+len;i<=S->length-1;i++)	/*将串S的第pos个位置以后的len个字符覆盖掉*/
					  S->str[i-len]=S->str[i];
				  S->length=S->length-len; 		/*修改串S的长度*/
				  return 1;
			 }
		}
		//将串S连接在串T的末尾。可分为两种情况：
		int StrConcat(SeqString *T,SeqString S)
        {
          /*第1种情况*/
          if(T->length+S.length<=MaxLen)
          {
				 for(i=T->length;i<T->length+S.length;i++)	
					  T->str[i]=S.str[i-T->length];
				 T->length=T->length+S.length; 	/*修改串T的长度*/
				 flag=1; 	/*修改标志，表示S完整连接到T中*/
          }
		  /*第2种情况*/
			else if(T->length<MaxLen)
		   {
				 for(i=T->length;i<MaxLen;i++)	/*将串S部分连接在T的末尾*/
					 T->str[i]=S.str[i-T->length];
				 T->length=MaxLen; 		 /*修改串T的长度*/
				 flag=0; 		/*修改标志，表示S部分被连接在T中*/
			}
			 return flag;
		}
		int Index(SeqString *S1,SeqString *S2)
		{
			int i=0,j,k;
			while(i<S1->length)
			{
				j=0;
				if(S1->str[i]==S2->str[j])
				{
					k=i+1;
					j++;
					while(k<S1->length && j<S2->length && S1->str[k]==S2->str[j])
					{
						k++;
						j++;
					}
					if(j==S2->length)
						break;
					else
						i++;
				}
				else
					i++;
			}
			if(i>=S1->length)
				return -1;
			else
				return i+1;
		}
		void DelAllString(SeqString *S1,SeqString *S2)
		{
			int n;
			n=Index(S1,S2);
			while(n>=0)
			{
				DelSubString(S1,n,StrLength(S2));
				n=Index(S1,S2);
			}
		}
        void StrPrint(SeqString S)
		{
			int i;
			for(i=0;i<S.length;i++)
			{
				printf("%c",S.str[i]);
			}
			printf("\n");
		}
10.【堆串ADT实现】
		InitString(HeapString *S)
		   /*串的初始化操作*/
		  {
			  S->length=0; 			/*将串的长度置为0*/
			  S->str='\0'; 			/*将串置的值为空*/
		  }
		  //将字符串cstr中的字符赋给串S。
		  void StrAssign(HeapString *S,char cstr[]) 
		 {
			  int i=0,len;
			  if(S->str)
				  free(S->str);
			  for(i=0;cstr[i]!=’\0’;i++);	/*求cstr字符串的长度*/
				  len=i;
			  if(!i)			/*如果字符串cstr的长度为0，则将串S的长度置为0，内容置为空*/
			 {
				 S->str=’\0’;
				 S->length=0;
			 }else{
				 S->str=(char*)malloc(len*sizeof(char)); 	/*为串动态分配存储空间*/
				 if(!S->str)
					 exit(-1);
				 for(i=0;i<len;i++)			/*将字符串cstr的内容赋值给串S*/
					 S->str[i]=cstr[i];
				 S->length=len; 			/*将串的长度置为0*/
			}
		}  
		   void StrCopy(HeapString *T,HeapString S) 
		  /*串的复制操作.*/
		  {
				int i;
				T->str=(char*)malloc(S.length*sizeof(char)); 	
			   /*为串动态分配存储空间*/
			   if(!T->str)
					exit(-1);
			   for(i=0;i<S.length;i++)					
			   /*将串S的字符赋值给串T*/
					T->str[i]=S.str[i];
			   T->length=S.length; 		/*将串S的长度赋值给串T*/
		  }
		   int StrInsert(HeapString *S,int pos,HeapString T)
		   /*在S中第pos个位置插入T */
		   {
				int i;
				if(pos<0||pos-1>S->length) 	/*插入位置不正确，返回0*/
			   {
					printf(“插入位置不正确”);
					return 0;
				}
			   S->str=(char*)realloc(S->str,(S->length+T.length)*sizeof(char));
			   if(!S->str)
			  {
				  printf(“内存分配失败”);
				  exit(-1);
			   }
			    for(i=S->length-1;i>=pos-1;i--)		/*将串S中第pos个位置的字符往后移动T.length个位置*/
                    S->str[i+T.length]=S->str[i];
				for(i=0;i<T.length;i++)				/*将串T的字符赋值到S中*/
					   S->str[pos+i-1]=T.str[i];
				  S->length=S->length+T.length;	/*修改串的长度*/
				  return 1;
			 }

11.【LinkString.h块链ADAT的实现】
      1）初始化块链串。
		void InitString(LinkString *S)
		/*初始化块链串*/
		{
			S->length=0; 			/*将串的长度置为0*/
			S->head=S->tail=NULL; 	/*将串的头指针和尾指针置为空*/
		}
		




---------------稀疏矩阵的基本运算的算法实现如下。
    三元组顺序表的类型描述如下。
	#define MaxSize 200
	typedef struct			/*三元组类型定义*/
	{
		int i; 			    /*非零元素的行号*/
		int j; 			    /*非零元素的列号*/
		DataType e;
	}Triple;
	typedef struct			/*矩阵类型定义*/
	{
		Triple data[MaxSize];
		int m; 			   /*矩阵的行数*/
		int n; 			   /*矩阵的列数*/
		int len; 		   /*矩阵中非零元素的个数*/
	}TriSeqMatrix;
   （1）稀疏矩阵的创建。
   int CreateMatrix(TriSeqMatrix *M)
  /*创建稀疏矩阵（按照行优先顺序输入非零元素值）*/
  { 
	int i,m,n;
	DataType e;
	int flag;
	printf("请输入稀疏矩阵的行数、列数及非零元素个数：");
	scanf("%d,%d,%d",&M->m,&M->n,&M->len);
	if(M->len>MaxSize)
		return 0;
	for(i=0;i<M->len;i++)
	{
		//输入非0元素的行号和列号，还有元素值，并确保行、列号正确。
		do
		{
		   printf("请按行序顺序输入第%d个非零元素所在的行(0～%d),列
						 (0～%d),元素值:",i+1,M->m-1,M->n-1);
		   scanf("%d,%d,%d",&m,&n,&e);
		   flag=0;			/*初始化标志位*/
		   if(m<0||m>M->m||n<0||n>M->n)			   
				/*如果行号或列号正确，标志位为0（循环结束），否则为1（继续执行程序，知道输入合法位置）*/
				   flag=1;                        
				/*若输入的顺序正确，则标志位为0（循环结束），否则为1*/
		  if(i>0&&((m<M->data[i-1].i||m==M->data[i-1].i))&&(n<=M->data[i-1].j))	
			   flag=1;
		}while(flag);
		M->data[i].i=m;
		M->data[i].j=n;
		M->data[i].e=e;
	}
	return 1;
}
（2）复制稀疏矩阵。
      void CopyMatrix(TriSeqMatrix M,TriSeqMatrix *N)
     //由稀疏矩阵M复制得到另一个副本N
     { 
	    int i;
	    N->len=M.len;	/*修改稀疏矩阵N的非零元素的个数*/
	    N->m=M.m;	    /*修改稀疏矩阵N的行数*/
	    N->n=M.n;		/*修改稀疏矩阵N的列数*/
	    for(i=0;i<M.len;i++)	/*把M中非零元素的行号、列号及元素值依次赋值给N的行号、列号及元素值*/
	   {
		  N->data[i].i=M.data[i].i;
		  N->data[i].j=M.data[i].j;
		  N->data[i].e=M.data[i].e;
	   }
     }
     （3）稀疏矩阵的转置。
    void TransposeMatrix(TriSeqMatrix M,TriSeqMatrix *N)
    { 
		int i,k,col;
		N->m=M.n;              //重置行数、列数
		N->n=M.m;           
		N->len=M.len;          //非0元素个数相等
		if(N->len)
		{
			k=0;
			for(col=0;col<M.n;col++)	//列号变为行号后，顺序打乱，需要重新按顺序排列		
				for(i=0;i<M.len;i++)
					if(M.data[i].j==col)		
					{
						N->data[k].i=M.data[i].j;
						N->data[k].j=M.data[i].i;
						N->data[k].e=M.data[i].e;
						k++;
					}
		}
	}
       void FastTransposeMatrix(TriSeqMatrix M,TriSeqMatrix *N)
		//快速稀疏矩阵的转置运算,动态数组存储
		{  
			int i,k,t,col,*num,*position;            //num和positiondo都为动态数组。
			//(M.n+1)表示num和position数组的长度/存放元素的个数。
			num=(int *)malloc((M.n+1)*sizeof(int));  //数组num用于存放M中的每一列非零元素个数*/
			position=(int *)malloc((M.n+1)*sizeof(int));    
			//初始化N
			N->n=M.n; 
			N->m=M.m;
			N->len=M.len;
			
			if(N->len) 
			{
				for(col=0;col<M.n;++col)
					num[col]=0;		/*初始化num数组*/
				for(t=0;t<M.len;t++)		/*计算M中每一列非零元素的个数*/
					num[M.data[t].j]++;     //这个句子很美，我第一次居然没看懂，哈哈
			  //相当于j=M.data[t].j;num[j]++;   //即获得非0元素的列坐标，哪一列就给那一列加1.
				position[0]=0;		/*N中第一行的第一个非零元素的序号为0*/
				for(col=1;col<M.n;col++)		/*将N中第col行的第一个非零元素的位置*/
					position[col]=position[col-1]+num[col-1]; 
				for(i=0;i<M.len;i++)			/*依据position对M进行转置，存入N*/
				{
					col=M.data[i].j; 
					k=position[col];		/*取出N中非零元素应该存放的位置，赋值给k*/
					N->data[k].i=M.data[i].j;
					N->data[k].j=M.data[i].i;
					N->data[k].e=M.data[i].e;
					position[col]++;	    /*修改下一个非零元素应该存放的位置*/
				}
			}
			free(num);
			free(position);
		}






























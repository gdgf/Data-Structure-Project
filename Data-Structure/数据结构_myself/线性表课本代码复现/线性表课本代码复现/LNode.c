#include"LNode.h"
void CreateList_L(LinkList L, int n) {
	//逆位序输入n个元素的值，建立带表头节点的单链线性表L.
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));//建立一个带头节点的单链表
	L->next = NULL;
	L->data = 0;
	int i;
	for (i = n; i > 0; --i) {
		p = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &(p->data));
		p->next = L->next;
		L->next = p;
	}
}

Status CreateList_HL(FILE *fp, LinkList *L, int n)
//头插法创建链表（逆序插入）
{
	int i;
	LinkList p;
	ElemType tmp;

	(*L) = (LinkList)malloc(sizeof(LNode));//建立头节点
	if (!(*L))exit(OVERFLOW);
	(*L)->next = NULL;             
	for (i = 1; i <= n; i++) {
		if (fscanf(fp, "%d", &tmp) == 1) {
			//建立结点
			p = (LinkList)malloc(sizeof(LNode));
			if (!p)exit(OVERFLOW);
			p->data = tmp;
			p->next = (*L)->next;
			(*L)->next = p;
		}
		else 
			return ERROR;
	}
	return OK;
}

Status CreateList_TL(FILE *fp, LinkList *L,int n)
//尾插法建立单链表（顺序插入）
{
	int i;
	LinkList p, q;
	ElemType tmp;
	(*L) = (LinkList)malloc(sizeof(LNode));
	if (!(*L))exit(OVERFLOW);
	(*L)->next = NULL;
	q = (*L);  //q指向头节点

	for (i = 1; i <= n; i++) {
		if (fscanf(fp, "%d", &tmp) == 1) {
			p = (LinkList)malloc(sizeof(LNode));
			if (!p)exit(OVERFLOW);
			p->data = tmp;
			q->next = p;
			q = p;
		}
		else
		{
			return ERROR;
		}
	}
	q->next = NULL;
	return OK;
}
Status ClearList_L(LinkList L)
//指控单链表，头节点保留
{
	LinkList pre, p;
	if (!L) return ERROR;
	pre = L->next;
	while (pre) {
		p = pre->next;
		free(pre);
		pre = p;
	}
	L->next = NULL;
	return OK;
}
void DestroyList_L(LinkList *L)
//销毁单链表L,头节点一起销毁
{
	LinkList p = *L;
	while (p) {
		p = (*L)->next;
		free(*L);
		(*L) = p;
	}
}
Status ListEmpty_L(LinkList L)
//判断单链表L是否为空
{
	if (L != NULL && L->next == NULL)
		return TRUE;
	else
		return FALSE;
}
int ListLength_L(LinkList L)
//返回单链表中的元素个数
{
	LinkList p;
	int i;
	if (L) {
		i = 0;
		p = L->next;
		while (p) {
			i++;
			p = p->next;
		}
	}
	return i;
}
int LocateElem_L(LinkList L, ElemType e, Status(Compare)(ElemType, ElemType))
//返回单链表L中第一个e与满足compare关系的元素位序
{
	int i;
	LinkList p;
	i = -1;
	if (L) {
		i = 0; 
		p = L->next;
		while (p) {
			i++;
			if (!Compare(e, p->data))
				p = p->next;
			else
				break;
		}
	}
	return i;
}
Status PriorElem_L(LinkList L, ElemType cur_e, ElemType *pre_e)
//用pre_e接收cur_e的前驱
{
	LinkList p, suc;
	if (L) {                        //L非空
		p = L->next;                //第一个结点
		if (p->data != cur_e) {     //没有节点
			while (p->next){
				suc = p->next;      
				if (suc->data == cur_e) {
					*pre_e = p->data;
					return OK;
				}
				p = suc;
			}
		}
	}
	return ERROR;
}

Status NextElem_L(LinkList L, ElemType cur_e, ElemType *next_e)
//用next_e接收cur_ed的前驱
{
	LinkList p, suc;
	if (L) {
		p = L->next;
		while (p&&p->next) {//p不空，且它的下一个也不空，不然没有后继
			suc = p->next;
			if (suc&&p->data == cur_e) {
				*next_e = suc->data;
				return OK;
			}
			if (suc)p = suc;
			else break;
		}
	}
	return ERROR;
}
Status ListTraverse_L(LinkList L, void(Visit)(ElemType))
//用Visit函数访问单链表L
{
	LinkList p;
	if (!L)return ERROR;  //没有头节点
	else p = L->next;
	while (p) {
		Visit(p->data);
		p = p->next;
	}
	return OK;
}

Status ListInit_L(LinkList *L) {
	(*L) = (LinkList)malloc(sizeof(LNode));
	if (!(*L))exit(OVERFLOW);
	(*L)->next = NULL;
	return OK;
}
Status GetElem_L(LinkList L, int i, ElemType *e) {
	
	//获得第i个元素
	LinkList p;
	p = L->next;       //L为带头结点的单链表的头指针，初始化，p指向第一个结点。
	int j = 1;         //j为计数器
	while (p&&j<i){    //顺时针向后查找，让指针一直往后面走，直到p指向第i个元素或p为空
		p = p->next;
		j++;              
	}
	if (!p || j > i)return ERROR;
	*e = p->data;
	return OK;
}

Status ListInsert_L(LinkList L, int i, ElemType e) {
	//在带头节点的单链线性表L中第i个位置之前插入元素e
	LinkList p=L;
	int j = 0;
	while (p&&j < i - 1) {             //寻找第i-1个结点
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)return ERROR;   //不符合条件
	LinkList s = (LinkList)malloc(sizeof(LNode));  //新结点
	s->data = e;                        //赋值
	s->next = p->next;                  //s指向原来的第i个元素的下一个元素
	p->next = s;                        //让第i-1个元素指向s
	return OK;
}

Status ListDelete_L(LinkList L, int i, ElemType *e) {
	LinkList q,p = L;
	int j = 0;
	while (p->next&&j < i - 1) {//寻找第i-1个结点，且p的下一个不为空
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)return ERROR;
	q = p->next;                       //q指向p的下一个即i
	p->next = q->next;                 //让p(i-1)的下一个为q的下一个,即i+1

	*e = q->data;                      //带回数据  
	free(q);                           //释放指针
	return OK;
}

void ListPrint_L(LinkList L) {
	LinkList p=L;
	p = p->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}

Status Compare(ElemType e1, ElemType e2) {
	//判断是否相等
	if (e1 == e2)return 1;
	else return 0;
}
void Visit(ElemType e) {
	printf("%d ", e);
}
#include"Algorithm.h"

//A=A∪B
void Union1(List1 *La, List1 Lb)
{
	int La_Len = La->Length;
	int Lb_Len = Lb.Length;
	int i;
	for (i = 1; i <= Lb_Len; i++) {
		ElementType e = 0;
		GetElEM1(Lb, i, &e);    //得到Lb中的第i个元素e     
		if (!LocateElem(*La, e))  //判断，如果La中不存在e的话怎将其插入
			List1Insert(La,++La_Len, e);
	}
}




//集合la和lb归并
void MergeList1(List1 La, List1 Lb, List1 *Lc) {
	
	InitList1(Lc);               //初始化新的线性表
	int La_Len = La.Length;
	int Lb_Len = Lb.Length;
	int i=1,j=1, k = 0;
	ElementType e1, e2;
	while ((i<=La_Len)&&(j<=Lb_Len))     //La，Lb两者均不空时，
	{
		//得到各自的第i，j个元素，比较，小的先插入Lc，记得插入后相应的序号要向后移动
		GetElEM1(La, i, &e1);            
		GetElEM1(Lb, j, &e2);
		if (e1 <= e2) {
			List1Insert(Lc, ++k, e1);
			++i;
		}
		else {
			List1Insert(Lc, ++k, e2);
			++j;
		}
	}
	//将没有空的一者的后续成员全部插入到Lc
	while (i <= La_Len) {
		GetElEM1(La, i++,&e1);
		List1Insert(Lc, ++k, e1);
	}
	while (i <= Lb_Len) {
		GetElEM1(Lb, i++, &e2);
		List1Insert(Lc, ++k, e2);
	}
}

//归并SqList实现版
void MergeList_Sq(SqList La, SqList Lb, SqList *Lc) {

	ElementType *pa, *pb,*pc;
	pa = La.elem;
	pb = Lb.elem;
	Lc->length = La.length + Lb.length;
	Lc->ListSize = Lc->length;

	Lc->elem = (ElementType*)malloc(Lc->ListSize * sizeof(ElementType));
	if (!Lc->elem) exit(OVERFLOW);
	pc = Lc->elem;

	ElementType *pa_last, *pb_last;
	pa_last = La.elem + La.length -1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa<=pa_last&&pb<=pb_last)
	{
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last)*pc++ = *pa++;
	while (pb <= pb_last)*pc++ = *pb++;

}

//Lode的归并算法
void MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc) {
	LinkList pa, pb,pc;
	pa = La->next;
	pb = (*Lb)->next;
	//用La的头节点作为Lc的头节点
	*Lc = La;
	pc = La;
	while (pa&&pb) {
		if (pa->data <= pb->data){
			pc->next = pa;  //链接
			pc = pa;         //跳转
			pa = pa->next;   //pa指向他的下一个
		}else{
			pc->next = pb;  //跳转
			pc = pb;         //
			pb = pb->next;
		}
	}
	//判断pa是否为空，若为空，则指向pb，不为空指向pa
	pc->next = pa ? pa : pb;
	free(*Lb);
	*Lb = NULL;
}

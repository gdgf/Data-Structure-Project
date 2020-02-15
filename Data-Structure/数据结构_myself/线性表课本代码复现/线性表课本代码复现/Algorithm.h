#pragma once
#include"SqList2.h"
#include"SqList.h"
#include"LNode.h"
//La=La∪Lb

void Union1(List1 *La, List1 Lb);
//集合la和lb归并
void MergeList1(List1 La, List1 Lb, List1 *Lc);
void MergeList_Sq(SqList La, SqList Lb, SqList *Lc);
void MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc);


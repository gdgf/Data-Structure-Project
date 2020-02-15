#pragma once
/*
线性表的静态单链表存储结构
*/
#include"预定义.h"
#define MAXSIZE 1000  //链表的最大长度

typedef struct {
	ElemType dats;
	int cur;
}component,SLinkList[MAXSIZE];


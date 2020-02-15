#pragma once
/*关于状态码的一点讨论*/
//函数结果状态码
#define  TRUE  1
#define  FALSE 0
#define  OK    1
#define  ERROR 0
#define  INFEASIBLE -1      //不可行
#define  OVERFLOW -2
typedef int Status;         //Status是函数的类型，其值是函数结果状态码

typedef int ElemType;


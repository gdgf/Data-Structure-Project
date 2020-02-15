#ifndef EVALUATEEXPRESSION_H_INCLUDED
#define EVALUATEEXPRESSION_H_INCLUDED
typedef int  SElemType;
typedef int  Status;
struct SqStack;
typedef struct SqStack SqStack;
//构造一个空栈
Status InitStack(SqStack *S);
Status StackEmpty(SqStack S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
//从栈底到栈顶依次对S的每个元素调用函数Visit（），一旦失败操作无效
//输出元素e
Status output(SElemType e);
Status in(char c,char op[]);
char Precede(char a, char b);
int Operate(int a, char theta, int b);
int getNext(int *n);
int EvaluateExpression();
#endif // EVALUATEEXPRESSION_H_INCLUDED

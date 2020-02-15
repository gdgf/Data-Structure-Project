#ifndef EVALUATEEXPRESSION_H_INCLUDED
#define EVALUATEEXPRESSION_H_INCLUDED
typedef int  SElemType;
typedef int  Status;
struct SqStack;
typedef struct SqStack SqStack;
//����һ����ջ
Status InitStack(SqStack *S);
Status StackEmpty(SqStack S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
//��ջ�׵�ջ�����ζ�S��ÿ��Ԫ�ص��ú���Visit������һ��ʧ�ܲ�����Ч
//���Ԫ��e
Status output(SElemType e);
Status in(char c,char op[]);
char Precede(char a, char b);
int Operate(int a, char theta, int b);
int getNext(int *n);
int EvaluateExpression();
#endif // EVALUATEEXPRESSION_H_INCLUDED

#include "stack_s.h"
#include <stdio.h>
#include "malloc.h"

#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW    -2
#define STACK_INIT_SIZE  100
#define STACKINCREMENT   10

typedef int  Status;
typedef int  SElemType;
struct SqStack{
    SElemType *base;
    SElemType *top;
    int      stacksize;
};
//����һ����ջ
Status InitStack(SqStack *S){
    S->base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));

    if(!S->base)
        exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
//�ж��Ƿ�Ϊ��ջ
Status StackEmpty(SqStack S){
    if(S.top == S.base)
        return TRUE;
    else
        return FALSE;
}
//��e����S�Ķ�Ԫ��
Status GetTop(SqStack S, SElemType *e){
    if(S.top == S.base)
        return ERROR;
    *e = *(S.top-1);
    return OK;
}
//����eΪ�µĶ�Ԫ��
Status Push(SqStack *S, SElemType e){
    if((S->top - S->base) >= S->stacksize){
        S->base = (
                    SElemType*)realloc(S->base,
                   (S->stacksize+STACKINCREMENT)*sizeof(SElemType)
                   );
        if(!S->base)
            exit(OVERFLOW);
        S->top = S->base +S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top)=e;
    S->top++;
    return OK;
}
//ɾ��S�Ķ�Ԫ�أ�����e������ֵ
Status Pop(SqStack *S, SElemType *e){
    if(S->top == S->base)
        return ERROR;
    S->top--;
    *e = *(S->top);
    return OK;
}
//��ջ�׵�ջ�����ζ�S��ÿ��Ԫ�ص��ú���Visit������һ��ʧ�ܲ�����Ч
Status ListTraverse(SqStack S,Status (*visit)(SElemType)){
    SElemType *p;
    p=S.base;
    for(p=S.base;p<S.top;p++)
        (*visit)(*p);

    return OK;
}
//���Ԫ��e
Status output(SElemType e){
    printf("%d ",e);

    return OK;
}
Status in(char c,char op[]){
    char *p;
    p=op;
    while(*p != '\0'){
        if(c == *p)
            return TRUE;
        p++;
    }
    return FALSE;
}
char Precede(char a, char b){
    int i,j;
    char pre[][7]={
    /*�����֮������ȼ�������һ�ű��*/
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}};
    switch(a){
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '(': i=4; break;
        case ')': i=5; break;
        case '#': i=6; break;
    }
    switch(b){
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '(': j=4; break;
        case ')': j=5; break;
        case '#': j=6; break;
    }
    return pre[i][j];
}
int Operate(int a, char theta, int b){
    int i,j,result;
    i=a;
    j=b;

    switch(theta)   {
        case '+': result = i + j; break;
        case '-': result = i - j; break;
        case '*': result = i * j; break;
        case '/': result = i / j; break;
    }
    return result;
}
int getNext(int *n){
    char c;
    *n=0;
    while((c=getchar())==' ');  /*����һ�������ո�*/
    if(!isdigit(c)){            /*ͨ�������ж�����ַ��������֣���ôֻ���������*/
        *n=c;
        return 1;
    }
    do    {                         /*��ִ�е�������䣬˵���ַ������֣��˴���ѭ���������������*/
        *n=*n*10+(c-'0');       /*�������������ַ�ת�������Ӧ������*/
        c=getchar();
    }    while(isdigit(c));         /*�����һ���ַ������֣�������һ��ѭ��*/
    ungetc(c,stdin);            /*�¶�����ַ��������֣������������,Ϊ�˲�Ӱ���´ζ��룬�Ѹ��ַ��Żص����뻺����*/
    return 0;
}

int EvaluateExpression(){

    int n;
    int flag;
    int c;
    char x,theta;
    int a,b;

    char OP[]="+-*/()#";
    SqStack  OPTR;
    SqStack  OPND;

    InitStack(&OPTR);
    Push(&OPTR,'#');
    InitStack(&OPND);
    flag=getNext(&c);

    GetTop(OPTR, &x);
    while(c!='#' || x != '#')
    {
        if(flag == 0)
         {
                  Push(&OPND,c);
                  flag = getNext(&c);
             }        else
    {
            GetTop(OPTR, &x);
            switch(Precede(x, c))
        {
                case '<'://ջ��Ԫ�����ȼ���
                    Push(&OPTR,c);
                    flag = getNext(&c);
                    break;
                case '='://�����Ų�������һ�ַ�
                    Pop(&OPTR,&x);
                    flag = getNext(&c);
                    break;
                case '>':// ��ջ������������ջ
                    Pop(&OPTR, &theta);
                    Pop(&OPND,&b);
                    Pop(&OPND,&a);
                    Push(&OPND, Operate(a, theta, b));
                    break;
            }
        }
        GetTop(OPTR, &x);
    }
    GetTop(OPND, &c);
    return c;
}

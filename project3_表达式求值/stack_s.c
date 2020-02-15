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
//构造一个空栈
Status InitStack(SqStack *S){
    S->base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));

    if(!S->base)
        exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
//判断是否为空栈
Status StackEmpty(SqStack S){
    if(S.top == S.base)
        return TRUE;
    else
        return FALSE;
}
//用e返回S的顶元素
Status GetTop(SqStack S, SElemType *e){
    if(S.top == S.base)
        return ERROR;
    *e = *(S.top-1);
    return OK;
}
//插入e为新的顶元素
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
//删除S的顶元素，并用e返回其值
Status Pop(SqStack *S, SElemType *e){
    if(S->top == S->base)
        return ERROR;
    S->top--;
    *e = *(S->top);
    return OK;
}
//从栈底到栈顶依次对S的每个元素调用函数Visit（），一旦失败操作无效
Status ListTraverse(SqStack S,Status (*visit)(SElemType)){
    SElemType *p;
    p=S.base;
    for(p=S.base;p<S.top;p++)
        (*visit)(*p);

    return OK;
}
//输出元素e
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
    /*运算符之间的优先级制作成一张表格*/
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
    while((c=getchar())==' ');  /*跳过一个或多个空格*/
    if(!isdigit(c)){            /*通过函数判断如果字符不是数字，那么只能是运算符*/
        *n=c;
        return 1;
    }
    do    {                         /*能执行到该条语句，说明字符是数字，此处用循环获得连续的数字*/
        *n=*n*10+(c-'0');       /*把连续的数字字符转换成相对应的整数*/
        c=getchar();
    }    while(isdigit(c));         /*如果下一个字符是数字，进入下一轮循环*/
    ungetc(c,stdin);            /*新读入的字符不是数字，可能是运算符,为了不影响下次读入，把该字符放回到输入缓冲区*/
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
                case '<'://栈顶元素优先级低
                    Push(&OPTR,c);
                    flag = getNext(&c);
                    break;
                case '='://脱括号并接受下一字符
                    Pop(&OPTR,&x);
                    flag = getNext(&c);
                    break;
                case '>':// 退栈并将运算结果入栈
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

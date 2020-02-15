#include <stdio.h>
#include "stack_s.h"
void main(){
    int c;
    printf("Please input one expression:");
    c=EvaluateExpression();
    printf("Result=%d\n",c);
}

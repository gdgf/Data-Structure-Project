#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED
typedef int DataType;
struct JoseNode;
typedef struct JoseNode JoseNode;

JoseNode JoseInit();
//单链表插入操作
int JoseInsert(JoseNode *h, int pos, DataType num,DataType passward);
//遍历
void TraverseList(JoseNode* h, int M);
//出列
void Column(JoseNode *h,int m);
#endif // LINKLIST_H_INCLUDED

#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED
typedef int DataType;
struct JoseNode;
typedef struct JoseNode JoseNode;

JoseNode JoseInit();
//������������
int JoseInsert(JoseNode *h, int pos, DataType num,DataType passward);
//����
void TraverseList(JoseNode* h, int M);
//����
void Column(JoseNode *h,int m);
#endif // LINKLIST_H_INCLUDED

#ifndef M_ARITHMETIC_H_INCLUDED
#define M_ARITHMETIC_H_INCLUDED
struct TriSeqMatrix;
typedef struct  TriSeqMatrix TriSeqMatrix;
int CreateMatrix(TriSeqMatrix *M);
//创建稀疏矩阵（按照行优先顺序输入非零元素值）
void PrintMatrix(TriSeqMatrix M);
//输出稀疏矩阵
int CompareElement(int a,int b);
//比较两个矩阵的元素值大小。前者小于后者，返回-1；相等，返回0；大于，返回1
int AddMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C);
//将两个矩阵A和B对应的元素值相加，得到另一个稀疏矩阵C
void MultMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C);
//稀疏矩阵A和B相乘得到C
int SubMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C);
//稀疏矩阵相减
void MultMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C);
//稀疏矩阵A和B相乘得到C
#endif // M_ARITHMETIC_H_INCLUDED

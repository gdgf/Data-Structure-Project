#ifndef M_ARITHMETIC_H_INCLUDED
#define M_ARITHMETIC_H_INCLUDED
struct TriSeqMatrix;
typedef struct  TriSeqMatrix TriSeqMatrix;
int CreateMatrix(TriSeqMatrix *M);
//����ϡ����󣨰���������˳���������Ԫ��ֵ��
void PrintMatrix(TriSeqMatrix M);
//���ϡ�����
int CompareElement(int a,int b);
//�Ƚ����������Ԫ��ֵ��С��ǰ��С�ں��ߣ�����-1����ȣ�����0�����ڣ�����1
int AddMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C);
//����������A��B��Ӧ��Ԫ��ֵ��ӣ��õ���һ��ϡ�����C
void MultMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C);
//ϡ�����A��B��˵õ�C
int SubMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C);
//ϡ��������
void MultMatrix(TriSeqMatrix A,TriSeqMatrix B,TriSeqMatrix *C);
//ϡ�����A��B��˵õ�C
#endif // M_ARITHMETIC_H_INCLUDED

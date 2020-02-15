#ifndef NATRSIMULATION_H_INCLUDED
#define NATRSIMULATION_H_INCLUDED
typedef short int NumType;
typedef struct TrafficWay{
    char name[15];    //�д�/���
    int DepTime;      //����ʱ��
    int ArriveTime;   //����ʱ��
    int DesCity;      //������б��
    int Price;        //Ʊ��
}TrafficWayDat;       //��ͨ������Ϣ
typedef struct CityNode{
   NumType city;             //���еĸ���
   int TrainNum,FlightNum;   //·��ĳ�����еĻ�/�ɻ��ı��
   TrafficWayDat Train[10];
   TrafficWayDat Flight[10];
}CityNodeDat;//
typedef struct PathNode {
    int City;        //����
    int FlainNo;     //�𳵻��ߺ���Ĵ˺�
}PathNodeDat;        //�洢·��
int Start();
//����
int InitSysData();
//��ʼ������
int AddCity (char *Name);
//��ӳ���
int FindNumofCity (char *name);
//���ҳ��У������س������
int DelCity (char *Name);
//ɾ������
int AddTrain(char *train,char *DepCity,char *DesCity,int DepTime,int EndTime,int cost);
//��ӻ�
int AddFlight(char *flight,char *DepCity,char *DesCity,int DepTime,int EndTime,int cost);
//��ӷɻ�����
int DelPath(char *name);
//ɾ��·��
void FindMinPrice_Print(int matx[34][34],int PreCity[34],int p_end,int ByTorByP);
//��ӡ��ͼ۸�·��
int CalcMinPrice(int DepCity,int DesCity,int ByTorByP);
//�������
void FindMinPrice(int matx[34][34],int p_start,int p_end,int ByTorByP);
//Ѱ����ͼ۸�·��
int SearchMinTime(NumType City,NumType DesCity,int CurTime,int curPathNo,int ByTorByP);
//Ѱ�����ʱ��·��
int CalcMinTime(int DepCity,int DesCity,int ByTorByP);
//����ʱ��
int SaveSysInfo();
//�洢����
#endif // NATRSIMULATION_H_INCLUDED

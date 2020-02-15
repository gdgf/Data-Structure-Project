#ifndef NATRSIMULATION_H_INCLUDED
#define NATRSIMULATION_H_INCLUDED
typedef short int NumType;
typedef struct TrafficWay{
    char name[15];    //列次/班次
    int DepTime;      //出发时间
    int ArriveTime;   //到达时间
    int DesCity;      //到达城市编号
    int Price;        //票价
}TrafficWayDat;       //交通工具信息
typedef struct CityNode{
   NumType city;             //城市的个数
   int TrainNum,FlightNum;   //路过某个城市的火车/飞机的编号
   TrafficWayDat Train[10];
   TrafficWayDat Flight[10];
}CityNodeDat;//
typedef struct PathNode {
    int City;        //城市
    int FlainNo;     //火车或者航班的此号
}PathNodeDat;        //存储路径
int Start();
//界面
int InitSysData();
//初始化数据
int AddCity (char *Name);
//添加城市
int FindNumofCity (char *name);
//查找城市，并返回城市序号
int DelCity (char *Name);
//删除城市
int AddTrain(char *train,char *DepCity,char *DesCity,int DepTime,int EndTime,int cost);
//添加火车
int AddFlight(char *flight,char *DepCity,char *DesCity,int DepTime,int EndTime,int cost);
//添加飞机航班
int DelPath(char *name);
//删除路径
void FindMinPrice_Print(int matx[34][34],int PreCity[34],int p_end,int ByTorByP);
//打印最低价格路线
int CalcMinPrice(int DepCity,int DesCity,int ByTorByP);
//计算费用
void FindMinPrice(int matx[34][34],int p_start,int p_end,int ByTorByP);
//寻找最低价格路线
int SearchMinTime(NumType City,NumType DesCity,int CurTime,int curPathNo,int ByTorByP);
//寻找最短时间路线
int CalcMinTime(int DepCity,int DesCity,int ByTorByP);
//计算时间
int SaveSysInfo();
//存储数据
#endif // NATRSIMULATION_H_INCLUDED

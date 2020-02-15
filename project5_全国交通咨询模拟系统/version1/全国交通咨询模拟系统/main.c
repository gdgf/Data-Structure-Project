#include <stdio.h>
#include <stdlib.h>
#include"NaTrSimulation.h"
int main()
{
   char name[15];
   char s_city[15];     //起点站城市
   char e_city[15];     //终点站城市
   int Command,cost;
   int DepCity,endcity,Vehicle;
   int s_hour,s_minute,e_hour,e_minute;
   while(1){
        Start();
        printf("请输入你要进行的步骤:");
        scanf("%d",&Command);
        switch(Command){
            case 1:
                   InitSysData();
                   printf("\n请输入城市名:");
                   scanf("%s",&name);
                   AddCity(name);
                   SaveSysInfo();
                   printf("添加成功!\n");
                   break;
             case 2:
                  InitSysData();
                  printf("\n输入城市名:");
                  scanf("%s",&name);
                  DelCity(name);
                  SaveSysInfo();
                  printf("删除成功!\n");
                  break;
             case 3:
                  InitSysData();
                  printf("起点站城市名:");
                  scanf("%s",&s_city);
                  printf("终点站城市名:");
                  scanf("%s",&e_city);
                  printf("类型(火车0，飞机1):");
                  scanf("%d",&Vehicle);
                  printf("输入火车/飞机航班:");
                  scanf("%s",&name);
                  printf("起始时间(00:00,24小时制):");
                  scanf("%2d:%2d",&s_hour,&s_minute);
                  printf("到达时间(00:00,24小时制):");
                  scanf("%2d:%2d",&e_hour,&e_minute);
                  printf("票价:");
                  scanf("%d",&cost);
                  if(Vehicle){
                        AddFlight(name,s_city,e_city,s_hour*60+s_minute,e_hour*60+e_minute,cost);
                  }else{
                        AddTrain(name,s_city,e_city,s_hour*60+s_minute,e_hour*60+e_minute,cost);
                  }
                  SaveSysInfo();
                  printf("添加路线成功!\n");
                  break;
             case 4:
                  InitSysData();
                  printf("输入火车车次/航班班次:");
                  scanf("%s",&name);
                  DelPath(name);
                  SaveSysInfo();
                  printf("删除路线成功!\n");
                  break;
             case 5:
                  InitSysData();
                  printf("\n起始城市:");
                  scanf("%s",&name);
                  DepCity=FindNumofCity(name);     //获得该城市的编号
                  if(DepCity<0){
                     printf("没有该城市信息!\n");
                     break;
                   }
                  printf("终点城市:");
                  scanf("%s",&name);
                  endcity=FindNumofCity(name);     //获得该城市的编号
                  if(endcity<0){
                      printf("没有该城市信息!\n");
                      break;
                   }
                   printf("选择要乘坐的交通工具(列车/飞机:0/1):");
                   scanf("%d",&Vehicle);
                   if(Vehicle!=0&&Vehicle!=1){
                        printf("输入错误!");
                        break;
                   }
                   CalcMinPrice(DepCity,endcity,Vehicle);
                   printf("\n");
                   break;
            case 6:
                 InitSysData();
                 printf("\n起始城市:");
                 scanf("%s",&name);
                 DepCity=FindNumofCity(name);
                 if(DepCity<0){
                    printf("没有该城市信息!\n");
                    break;
                 }
                 printf("终点城市:");
                 scanf("%s",&name);
                 endcity=FindNumofCity(name);
                 if(endcity<0){
                     printf("没有该城市信息!\n");
                     break;
                  }
                  printf("选择要乘坐的交通工具(列车/飞机:0/1):");
                  scanf("%d",&Vehicle);
                  if(Vehicle!=0&&Vehicle!=1){
                        printf("输入错误!");
                       break;
                  }
                  CalcMinTime(DepCity,endcity,Vehicle);
                  printf("\n");
                  break;
            case 0:
                  return 0;
            }
        }
}

#include <stdio.h>
#include <stdlib.h>
#include"NaTrSimulation.h"
int main()
{
   char name[15];
   char s_city[15];     //���վ����
   char e_city[15];     //�յ�վ����
   int Command,cost;
   int DepCity,endcity,Vehicle;
   int s_hour,s_minute,e_hour,e_minute;
   while(1){
        Start();
        printf("��������Ҫ���еĲ���:");
        scanf("%d",&Command);
        switch(Command){
            case 1:
                   InitSysData();
                   printf("\n�����������:");
                   scanf("%s",&name);
                   AddCity(name);
                   SaveSysInfo();
                   printf("��ӳɹ�!\n");
                   break;
             case 2:
                  InitSysData();
                  printf("\n���������:");
                  scanf("%s",&name);
                  DelCity(name);
                  SaveSysInfo();
                  printf("ɾ���ɹ�!\n");
                  break;
             case 3:
                  InitSysData();
                  printf("���վ������:");
                  scanf("%s",&s_city);
                  printf("�յ�վ������:");
                  scanf("%s",&e_city);
                  printf("����(��0���ɻ�1):");
                  scanf("%d",&Vehicle);
                  printf("�����/�ɻ�����:");
                  scanf("%s",&name);
                  printf("��ʼʱ��(00:00,24Сʱ��):");
                  scanf("%2d:%2d",&s_hour,&s_minute);
                  printf("����ʱ��(00:00,24Сʱ��):");
                  scanf("%2d:%2d",&e_hour,&e_minute);
                  printf("Ʊ��:");
                  scanf("%d",&cost);
                  if(Vehicle){
                        AddFlight(name,s_city,e_city,s_hour*60+s_minute,e_hour*60+e_minute,cost);
                  }else{
                        AddTrain(name,s_city,e_city,s_hour*60+s_minute,e_hour*60+e_minute,cost);
                  }
                  SaveSysInfo();
                  printf("���·�߳ɹ�!\n");
                  break;
             case 4:
                  InitSysData();
                  printf("����𳵳���/������:");
                  scanf("%s",&name);
                  DelPath(name);
                  SaveSysInfo();
                  printf("ɾ��·�߳ɹ�!\n");
                  break;
             case 5:
                  InitSysData();
                  printf("\n��ʼ����:");
                  scanf("%s",&name);
                  DepCity=FindNumofCity(name);     //��øó��еı��
                  if(DepCity<0){
                     printf("û�иó�����Ϣ!\n");
                     break;
                   }
                  printf("�յ����:");
                  scanf("%s",&name);
                  endcity=FindNumofCity(name);     //��øó��еı��
                  if(endcity<0){
                      printf("û�иó�����Ϣ!\n");
                      break;
                   }
                   printf("ѡ��Ҫ�����Ľ�ͨ����(�г�/�ɻ�:0/1):");
                   scanf("%d",&Vehicle);
                   if(Vehicle!=0&&Vehicle!=1){
                        printf("�������!");
                        break;
                   }
                   CalcMinPrice(DepCity,endcity,Vehicle);
                   printf("\n");
                   break;
            case 6:
                 InitSysData();
                 printf("\n��ʼ����:");
                 scanf("%s",&name);
                 DepCity=FindNumofCity(name);
                 if(DepCity<0){
                    printf("û�иó�����Ϣ!\n");
                    break;
                 }
                 printf("�յ����:");
                 scanf("%s",&name);
                 endcity=FindNumofCity(name);
                 if(endcity<0){
                     printf("û�иó�����Ϣ!\n");
                     break;
                  }
                  printf("ѡ��Ҫ�����Ľ�ͨ����(�г�/�ɻ�:0/1):");
                  scanf("%d",&Vehicle);
                  if(Vehicle!=0&&Vehicle!=1){
                        printf("�������!");
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

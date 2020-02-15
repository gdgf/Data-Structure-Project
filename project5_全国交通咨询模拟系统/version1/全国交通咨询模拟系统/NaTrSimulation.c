#include<stdio.h>
#include<string.h>
#include"NaTrSimulation.h"
CityNodeDat CityInfo[33];       //������Ϣ
char CityName[33][15];          //������
int NumofCity;                  //������Ŀ
PathNodeDat TemPath[33];        //��ʱ·��
PathNodeDat MinPath[33];        //���·��
int MinTime;                    //���ʱ��
int DepTime;
int curPath;
char CityFile[]="C:\\Users\\wangkai\\Desktop\\ȫ����ͨ��ѯģ��ϵͳ\\city.txt";
char TrainFile[]="C:\\Users\\wangkai\\Desktop\\ȫ����ͨ��ѯģ��ϵͳ\\train.txt";
char FlightFile[]="C:\\Users\\wangkai\\Desktop\\ȫ����ͨ��ѯģ��ϵͳ\\flight.txt";
int Start()
{
    printf("*-----------��ϵͳ��ʾ˵��------------*\n");
    printf("*ѡ����Ҫ���еĲ���:                  *\n");
    printf("*           1:��ӳ��У�              *\n");
    printf("*           2:ɾ�����У�              *\n");
    printf("*           3:��ӽ�ͨ·�ߣ�          *\n");
    printf("*           4:ɾ����ͨ·�ߣ�          *\n");
    printf("*           5:���Ҽ۸����·�ߣ�      *\n");
    printf("*           6:����ʱ�����·�ߣ�      *\n");
    printf("*           0:�˳�ϵͳ                *\n");
    printf("*-------------------------------------*\n");
    return 1;
}
int InitSysData()
//��ʼ������
{
    FILE *fp;
    int i,j,hour,minute,num,cost;
    char String1[15];
    char String2[15];
    char String3[15];
    //��ʼ��������Ϣ��
    fp=fopen(CityFile,"r");
    if(!fp){
        printf("�ļ��򿪳���!\n");
        return -1;
    }
    fscanf(fp,"%d",&NumofCity);          //���������Ŀ
    for(i=0;i<NumofCity;i++)
    {
        fscanf(fp,"%s",&CityName[i]);    //�����������
        CityInfo[i].city=i;              //�����б��
        CityInfo[i].TrainNum=0;          //����Ŀ�ݶ�Ϊ0
        CityInfo[i].FlightNum=0;         //�ɻ���Ŀ�ݶ�Ϊ0
    }
    fclose(fp);
    //��ʼ����·����Ϣ��
    fp=fopen(TrainFile,"r");
    if(!fp){
        printf("\n�ļ��򿪴���\n���ȳ�ʼ��ϵͳ����!");
        return -1;
    }
    fscanf(fp,"%d",&num);                   //��ͨ������Ŀ
    for(i=0;i<num;i++){
        fscanf(fp,"%s",&String1);           //�����г���
        fscanf(fp,"%s",&String2);           //������ʼ�ص�
        fscanf(fp,"%s",&String3);           //����Ŀ�ĵ�
        j=FindNumofCity(String2);           //��ȡ���б��
        //·���˳��еĻ𳵵�Ŀ�ĵ�
        CityInfo[j].Train[CityInfo[j].TrainNum].DesCity=FindNumofCity(String3);
        strcpy(CityInfo[j].Train[CityInfo[j].TrainNum].name,String1);//���θ������г�
        fscanf(fp,"%d:%d",&hour,&minute);   //�������ʱ��
        CityInfo[j].Train[CityInfo[j].TrainNum].DepTime=hour*60+minute;
        fscanf(fp,"%d:%d",&hour,&minute);   //���뵽��ʱ��
        CityInfo[j].Train[CityInfo[j].TrainNum].ArriveTime=hour*60+minute;
        fscanf(fp,"%d",&cost);              //�������
        CityInfo[j].Train[CityInfo[j].TrainNum].Price=cost;
        CityInfo[j].TrainNum++;
    }
    fclose(fp);
    //��ʼ���ɻ�·����Ϣ��һ��ͬ�ϡ�
    fp=fopen(FlightFile,"r");
    if(!fp){
        printf("\n�ļ��򿪴���!\n���ȳ�ʼ��ϵͳ����!");
        return -1;
    }
    fscanf(fp,"%d",&num);
    for(i=0;i<num;i++){
        fscanf(fp,"%s",&String1);
        fscanf(fp,"%s",&String2);
        fscanf(fp,"%s",&String3);
        j=FindNumofCity(String2);
        CityInfo[j].Flight[CityInfo[j].FlightNum].DesCity=FindNumofCity(String3);
        strcpy(CityInfo[j].Flight[CityInfo[j].FlightNum].name,String1);
        fscanf(fp,"%d:%d",&hour,&minute);
        CityInfo[j].Flight[CityInfo[j].FlightNum].DepTime=hour*60+minute;
        fscanf(fp,"%d:%d",&hour,&minute);
        CityInfo[j].Flight[CityInfo[j].FlightNum].ArriveTime=hour*60+minute;
        fscanf(fp,"%d",&cost);
        CityInfo[j].Flight[CityInfo[j].FlightNum].Price=cost;
        CityInfo[j].FlightNum++;
    }
    fclose(fp);
    return 1;
}
int AddCity(char *Name)
//��ӳ���
{
    strcpy(CityName[NumofCity],Name);     //��i������
    CityInfo[NumofCity].city=NumofCity;
    CityInfo[NumofCity].TrainNum=0;
    CityInfo[NumofCity].FlightNum=0;
    NumofCity++;
    return 1;
}
int FindNumofCity (char *name)
//���ҳ��е����
{
    int i;
    for (i=0;i<NumofCity;i++)
        if(strcmp(name,CityName[i])==0)
           return i;
    return -1;
}
int DelCity(char *Name)
//ɾ������
{
    int city,i,j;
    city=FindNumofCity(Name);     //�ҵ����еı��
    for(i=city;i<NumofCity-1;i++){    //ǰ��
        strcpy(CityName[i],CityName[i+1]);    //������
        CityInfo[i].TrainNum=CityInfo[i+1].TrainNum;  //��
        CityInfo[i].FlightNum=CityInfo[i+1].FlightNum; //����
        for(j=0;j<CityInfo[i].TrainNum;j++){   //ɾ���˵صĻ���Ϣ
            CityInfo[i].Train[j].Price=CityInfo[i+1].Train[j].Price;
            CityInfo[i].Train[j].DesCity=CityInfo[i+1].Train[j].DesCity;
            strcpy(CityInfo[i].Train[j].name,CityInfo[i+1].Train[j].name);
            CityInfo[i].Train[j].DepTime=CityInfo[i+1].Train[j].DepTime;
            CityInfo[i].Train[j].ArriveTime=CityInfo[i+1].Train[j].ArriveTime;
        }
        for(j=0;j<CityInfo[i].FlightNum;j++){   //ɾ���˵صĺ�����Ϣ
            CityInfo[i].Flight[j].Price=CityInfo[i+1].Flight[j].Price;
            CityInfo[i].Flight[j].DesCity=CityInfo[i+1].Flight[j].DesCity;
            strcpy(CityInfo[i].Flight[j].name,CityInfo[i+1].Flight[j].name);
            CityInfo[i].Flight[j].DepTime=CityInfo[i+1].Flight[j].DepTime;
            CityInfo[i].Flight[j].ArriveTime=CityInfo[i+1].Flight[j].ArriveTime;
        }
    }
    NumofCity--;
    return 1;
}
int AddTrain(char *train,char *DepCity,char *DesCity,int DepTime,int EndTime,int cost)
//��������ӻ�
{
    int i,j;
    i=FindNumofCity(DepCity);     //��ʼ���б��
    j=FindNumofCity(DesCity);     //Ŀ�ĵس��б��
    CityInfo[i].Train[CityInfo[i].TrainNum].Price=cost;     //����
	CityInfo[i].Train[CityInfo[i].TrainNum].DesCity=j;      //��i->j
	CityInfo[i].Train[CityInfo[i].TrainNum].DepTime=DepTime;  //��ʼʱ��
	CityInfo[i].Train[CityInfo[i].TrainNum].ArriveTime=EndTime;//����ʱ��
	strcpy(CityInfo[i].Train[CityInfo[i].TrainNum].name,train);//�г����
	CityInfo[i].TrainNum++;      //�Ӵ˳��еĳ����ĳ���+1
	return 1;
}
int AddFlight(char *flight,char *DepCity,char *DesCity,int DepTime,int EndTime,int cost)
//��������Ӻ���
{
    int i,j;
    i=FindNumofCity(DepCity);
    j=FindNumofCity(DesCity);
    CityInfo[i].Flight[CityInfo[i].FlightNum].Price=cost;
    CityInfo[i].Flight[CityInfo[i].FlightNum].DesCity=j;
    CityInfo[i].Flight[CityInfo[i].FlightNum].DepTime=DepTime;
    CityInfo[i].Flight[CityInfo[i].FlightNum].ArriveTime=EndTime;
    strcpy(CityInfo[i].Flight[CityInfo[i].FlightNum].name,flight);
    CityInfo[i].FlightNum++;
    return 1;
}
int DelPath(char *name)
//ɾ����//����
{
    int i;
    int j;
    int flag=0;
    for(i=0;i<NumofCity;i++){
        //ɾ����
        for(j=0;j<CityInfo[i].TrainNum;j++)
            if (strcmp(CityInfo[i].Train[j].name,name)==0){
                    flag=1;
                    break;
            }
        if(flag){
            for (;j<CityInfo[i].TrainNum-1;j++){
                CityInfo[i].Train[j].Price=CityInfo[i].Train[j+1].Price;
                CityInfo[i].Train[j].DesCity=CityInfo[i].Train[j+1].DesCity;
                strcpy(CityInfo[i].Train[j].name,CityInfo[i].Train[j+1].name);
                CityInfo[i].Train[j].DepTime=CityInfo[i].Train[j+1].DepTime;
                CityInfo[i].Train[j].ArriveTime=CityInfo[i].Train[j+1].ArriveTime;
            }
            CityInfo[i].TrainNum--;
            break;
        }
        //ɾ������
        for(j=0;j<CityInfo[i].FlightNum;j++)
             if(strcmp(CityInfo[i].Flight[j].name,name)==0){
                 flag=1;
                 break;
             }
         if(flag){
            for(;j<CityInfo[i].FlightNum-1;j++){
                CityInfo[i].Flight[j].Price=CityInfo[i].Flight[j+1].Price;
                CityInfo[i].Flight[j].DesCity=CityInfo[i].Flight[j+1].DesCity;
                strcpy(CityInfo[i].Flight[j].name,CityInfo[i].Flight[j+1].name);
                CityInfo[i].Flight[j].DepTime=CityInfo[i].Flight[j+1].DepTime;
                CityInfo[i].Flight[j].ArriveTime=CityInfo[i].Flight[j+1].ArriveTime;
		     }
		     CityInfo[i].FlightNum--;
		     break;
        }
    }
    return 1;
}
void FindMinPrice_Print(int matx[34][34],int PreCity[34],int p_end,int Vehicle)
//��ӡ��ͷ��÷���·��
{
    int track[34];
    int i=0,j,k,min,tmp,end,cost=0;
    j=p_end;
    track[i++]=j;
    while(PreCity[j]>=0){     //�����ͷ���
        cost+=matx[PreCity[j]][j];
        track[i++]=j=PreCity[j];
    }
    printf("\n����·��:");
    if(!Vehicle){
        for(i--;i>0;i--){
            printf("\n%s:",CityName[track[i]]);
            end=track[i-1];
            min=32767;
            for(k=0;k<CityInfo[track[i]].TrainNum;k++)
                if(CityInfo[track[i]].Train[k].DesCity==end&&min>CityInfo[track[i]].Train[k].Price){
                    min=CityInfo[track[i]].Train[k].Price;
                    tmp=k;
                }
            printf("�����%s���г�����ֹʱ��:",CityInfo[track[i]].Train[tmp].name);
            printf("%02d:%02d-%02d:%02d",CityInfo[track[i]].Train[tmp].DepTime/60,CityInfo[track[i]].Train[tmp].DepTime%60,CityInfo[track[i]].Train[tmp].ArriveTime/60,CityInfo[track[i]].Train[tmp].ArriveTime%60);
       }
    }else{
        for(i--;i>0;i--){
            printf("\n%s:",CityName[track[i]]);
            end=track[i-1];
            min=32767;
            for(k=0;k<CityInfo[track[i]].FlightNum;k++)
                if(CityInfo[track[i]].Train[k].DesCity==end&&min>CityInfo[track[i]].Flight[k].Price){
                    min=CityInfo[track[i]].Flight[k].Price;
                    tmp=k;
                }
            printf("�����%s�κ��࣬��ֹʱ��:",CityInfo[track[i]].Flight[tmp].name);
            printf("%02d:%02d-%02d:%02d",CityInfo[track[i]].Flight[tmp].DepTime/60,CityInfo[track[i]].Flight[tmp].DepTime%60,CityInfo[track[i]].Flight[tmp].ArriveTime/60,CityInfo[track[i]].Flight[tmp].ArriveTime%60);
        }
    }
    printf("\n%s:�ѵ���Ŀ�ĵ�",CityName[track[0]]);
    printf("\n��ͼ۸�:%d\n",cost);
}
void FindMinPrice(int matx[34][34],int p_start,int p_end,int Vehicle)
//Ѱ����ͷ���·��,(�Ͻ�˹�����㷨)
{
    int PreCity[34];
    int i,j,min,pre,pos;
    for(i=0;i<NumofCity;i++)    //��ʼ�������г��б��Ϊ-1
       PreCity[i]=-1;
    PreCity[p_start]=-2;        //����ʼ���б��Ϊ-2
    while(PreCity[p_end]==-1){
        min=-1;
        for(i=0;i<NumofCity;i++)
            if(PreCity[i]!=-1){  //��ʼ����
                for(j=0;j<NumofCity;j++)
                   if(PreCity[j]==-1&&matx[i][j]>0&&(min<0||matx[i][j]<min)){
                       pre=i;
                       pos=j;
                       min=matx[i][j];
                    }
            }
        PreCity[pos]=pre;
    }
    FindMinPrice_Print(matx,PreCity,p_end,Vehicle);
}
int CalcMinPrice(int DepCity,int DesCity,int Vehicle)
//������ͷ���,�õ��Ͻ�˹�����㷨
{
   int ma[34][34];                //�洢����֮��ļ۸�
   int i,j,min,end;
   for(i=0;i<NumofCity;i++)       //��ʼ��,����֮��ļ۸�ֵ-1��
      for(j=0;j<NumofCity;j++)
         ma[i][j]=-1;
    //�൱�ڸ�Ȩֵ
   if(Vehicle==0){                 //������
        //���������Ϣ��������������֮�����ͼ۸�ֱ�
       for(i=0;i<NumofCity;i++){
            min=32767;
			j=0;
            while(j<CityInfo[i].TrainNum){
                min=32767;
                end=CityInfo[i].Train[j].DesCity;
                //��i����->j����֮�����ͼ۸�(���Դ��ڶ����г����۸�һ)
                while(end==CityInfo[i].Train[j].DesCity&&j<CityInfo[i].TrainNum){
                    if(CityInfo[i].Train[j].Price<min)
                        min=CityInfo[i].Train[j].Price;
					j++;
                }
                ma[i][end]=min;
            }
        }
    }else{                        //�����ɻ�
        for(i=0;i<NumofCity;i++){
            min=32767;
            j=0;
            while(j<CityInfo[i].FlightNum){
                min=32767;
                end=CityInfo[i].Flight[j].DesCity;
                while(end==CityInfo[i].Flight[j].DesCity&&j<CityInfo[i].FlightNum){
                    if(CityInfo[i].Flight[j].Price<min)
                        min=CityInfo[i].Flight[j].Price;
                    j++;
                }
                ma[i][end]=min;
            }
        }
    }
    FindMinPrice(ma,DepCity,DesCity,Vehicle);
    return 1;
}
int SearchMinTime(NumType City,NumType DesCity,int CurTime,int curPathNo,int Vehicle)
//Ѱ����Сʱ��,(�Ͻ�˹�����㷨)
{
    int i;
    if(City==DesCity){
        if(MinTime>CurTime-DepTime){
           for(i=0;i<=curPathNo;i++){
               MinPath[i].City=TemPath[i].City;
               MinPath[i].FlainNo=TemPath[i].FlainNo;
               curPath=curPathNo;
            }
            if(CurTime<DepTime)
                MinTime=CurTime+1440-DepTime;
             else
				MinTime=CurTime-DepTime;
       }
     }else{
         curPathNo++;
         TemPath[curPathNo].City=City;
         if(!Vehicle){     //��
             for(i=0;i<CityInfo[City].TrainNum;i++){
                  if((CityInfo[City].Train[i].DepTime>=(CurTime%1440))&&(CityInfo[City].Train[i].ArriveTime+(CurTime/1440)*1440-DepTime<MinTime)){
                       TemPath[curPathNo].FlainNo=i;
                        SearchMinTime(CityInfo[City].Train[i].DesCity,DesCity,CityInfo[City].Train[i].ArriveTime+(CurTime/1440)*1440,curPathNo,Vehicle);
                   }
                   if((CityInfo[City].Train[i].DepTime<(CurTime%1440))&&(CityInfo[City].Train[i].ArriveTime+(CurTime/1440)*1440-DepTime<MinTime))
                   {
                        TemPath[curPathNo].FlainNo=i;
                        SearchMinTime(CityInfo[City].Train[i].DesCity,DesCity,CityInfo[City].Train[i].ArriveTime+(CurTime/1440+1)*1440,curPathNo,Vehicle);
                   }
              }
         }else{           //�ɻ�
             for(i=0;i<CityInfo[City].FlightNum;i++){
                if((CityInfo[City].Flight[i].DepTime>=CurTime)&&(CityInfo[City].Flight[i].ArriveTime+(CurTime/1440)*1440-DepTime<MinTime)){
                      TemPath[curPathNo].FlainNo=i;
                      SearchMinTime(CityInfo[City].Flight[i].DesCity,DesCity,CityInfo[City].Flight[i].ArriveTime+(CurTime/1440)*1440,curPathNo,Vehicle);
                }
                if((CityInfo[City].Flight[i].DepTime<CurTime)&&(CityInfo[City].Flight[i].ArriveTime+(CurTime/1440)*1440-DepTime<MinTime)){
                      TemPath[curPathNo].FlainNo=i;
					  SearchMinTime(CityInfo[City].Flight[i].DesCity,DesCity,CityInfo[City].Flight[i].ArriveTime+(CurTime/1440+1)*1440,curPathNo,Vehicle);
                }
            }
         }
    }
    return 1;
}
int CalcMinTime(int DepCity,int DesCity,int Vehicle)
//������Сʱ��
{
   int i;
   MinTime=32767;      //���ֵ
   curPath=0;
   TemPath[0].City=DepCity;
   if(!Vehicle){       //��
       for(i=0;i<CityInfo[DepCity].TrainNum;i++){
           TemPath[0].FlainNo=i;
           DepTime=CityInfo[DepCity].Train[i].DepTime;
           SearchMinTime(CityInfo[DepCity].Train[i].DesCity,DesCity,CityInfo[DepCity].Train[i].ArriveTime,0,Vehicle);
        }
    }else{            //�ɻ�
        for(i=0;i<CityInfo[DepCity].FlightNum;i++){
            TemPath[0].FlainNo=i;
            DepTime=CityInfo[DepCity].Flight[i].DepTime;
            SearchMinTime(CityInfo[DepCity].Flight[i].DesCity,DesCity,CityInfo[DepCity].Flight[i].ArriveTime,0,Vehicle);
        }
    }
    if(MinTime==32767){
        printf("\nϵͳ���޸�·�ߣ�");
        return 0;
    }
    printf("\n����·��:\n");
    for(i=0;i<=curPath;i++){
        if(!Vehicle)
           printf("%s:�����%s���г���ֹʱ��:",CityName[MinPath[i].City],CityInfo[MinPath[i].City].Train[MinPath[i].FlainNo].name);//��ӡ�������ͳ���
        else
           printf("%s:�����%s�κ���",CityName[MinPath[i].City],CityInfo[MinPath[i].City].Flight[MinPath[i].FlainNo].name);//��ӡ�������ͷɻ�����
        printf("%02d:%02d---%02d:%02d\n",CityInfo[MinPath[i].City].Train[MinPath[i].FlainNo].DepTime/60,CityInfo[MinPath[i].City].Train[MinPath[i].FlainNo].DepTime%60,CityInfo[MinPath[i].City].Train[MinPath[i].FlainNo].ArriveTime/60,CityInfo[MinPath[i].City].Train[MinPath[i].FlainNo].ArriveTime%60);
    }
    printf("%s:�ѵ���Ŀ�ĵ�",CityName[DesCity]);
	printf("\n��;�ķ�ʱ��:%02d:%02d",MinTime/60,MinTime%60);
	return 1;
}
int SaveSysInfo()
//������Ϣ
{
    FILE *fp;
    int i,j,total;
    //д�������Ϣ
    fp=fopen(CityFile,"w");
    fprintf(fp,"%d\n",NumofCity);
    for(i=0;i<NumofCity;i++)
        fprintf(fp,"%s\n",CityName[i]);
    fclose(fp);
    //д��𳵵���Ϣ
	total=0;
	fp=fopen(TrainFile,"w");
	for(i=0;i<NumofCity;i++)
        total+=CityInfo[i].TrainNum;
    fprintf(fp,"%d\n",total);
	for(i=0;i<NumofCity;i++){
        for(j=0;j<CityInfo[i].TrainNum;j++){
            //д���г�������ʼ���С��յ����
            fprintf(fp,"%s %s %s ",CityInfo[i].Train[j].name,CityName[i],CityName[CityInfo[i].Train[j].DesCity]);
            //д����ʼʱ��
            fprintf(fp,"%2d:%2d ",CityInfo[i].Train[j].DepTime/60,CityInfo[i].Train[j].DepTime%60);
            //д�뵽��ʱ�䡢����
            fprintf(fp,"%2d:%2d ",CityInfo[i].Train[j].ArriveTime/60,CityInfo[i].Train[j].ArriveTime%60);
            //д������
            fprintf(fp,"%d\n",CityInfo[i].Train[j].Price);
        }
    }
    fclose(fp);
    //д��ɻ�����Ϣ
    total=0;
    fp=fopen(FlightFile,"w");
    for(i=0;i<NumofCity;i++)
        total+=CityInfo[i].FlightNum;
    fprintf(fp,"%d\n",total);
	for(i=0;i<NumofCity;i++){
	    for(j=0;j<CityInfo[i].FlightNum;j++){
            fprintf(fp,"%s %s %s ",CityInfo[i].Flight[j].name,CityName[i],CityName[CityInfo[i].Flight[j].DesCity]);
            fprintf(fp,"%2d:%2d ",CityInfo[i].Flight[j].DepTime/60,CityInfo[i].Flight[j].DepTime%60);
            fprintf(fp,"%2d:%2d ",CityInfo[i].Flight[j].ArriveTime/60,CityInfo[i].Flight[j].ArriveTime%60);
            fprintf(fp,"%d\n",CityInfo[i].Flight[j].Price);
        }
    }
    fclose(fp);
	return 1;
}

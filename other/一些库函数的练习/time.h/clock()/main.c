#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define INFINITY 65535			            /*����һ�����޴��ֵ*/
#define MaxSize 50				            /*��󶥵����*/
typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
typedef int PathMatrix[MaxSize][MaxSize];	/*����һ���������·���Ķ�ά����*/
typedef int ShortPathLength[MaxSize];		/*����һ������Ӷ���v0������v����̾��������*/
typedef enum{DG,DN,UG,UN}GraphKind; 	    /*ͼ�����ͣ�����ͼ��������������ͼ��������*/
typedef struct
{
	VRType adj;				    /*������Ȩͼ����1��ʾ���ڣ�0��ʾ�����ڣ����ڴ�Ȩͼ���洢Ȩֵ*/
	InfoPtr *info; 				/*�뻡��ߵ������Ϣ*/
}ArcNode,AdjMatrix[MaxSize][MaxSize];
typedef struct					/*ͼ�����Ͷ���*/
{
	VertexType vex[MaxSize]; 	/*���ڴ洢����*/
	AdjMatrix arc; 				/*�ڽӾ��󣬴洢�߻򻡵���Ϣ*/
	int vexnum,arcnum; 			/*�������ͱߣ���������Ŀ*/
	GraphKind kind; 			/*ͼ������*/
}MGraph;
typedef struct 					/*���һ���洢�����С��к�Ȩֵ�����Ͷ���*/
{
	int row;
	int col;
	int weight;
}GNode;
void CreateGraph(MGraph *N,GNode *value,int vnum,int arcnum,VertexType *ch);
void DisplayGraph(MGraph N);
void Dijkstra(MGraph N,int v0,PathMatrix path,ShortPathLength dist);
void main()
{
	int i,vnum=6,arcnum=8;
    MGraph N;
    GNode value[]={{0,2,15},{0,4,30},{0,5,100},{1,2,10},
	{2,3,50},{3,5,10},{4,3,20},{5,4,60}};
    VertexType ch[]={"v0","v1","v2","v3","v4","v5"};
    PathMatrix path;						/*�ö�ά���������·���������Ķ���*/
    ShortPathLength dist;					/*��һά���������·������*/
    CreateGraph(&N,value,vnum,arcnum,ch);   /*����������N*/
    DisplayGraph(N);						/*���������N*/
    Dijkstra(N,0,path,dist);
    printf("%s������������·������Ϊ��\n",N.vex[0]);
    for(i=0;i<N.vexnum;i++)
        if(i!=0)
            printf("%s-%s:%d\n",N.vex[0],N.vex[i],dist[i]);
}
void CreateGraph(MGraph *N,GNode *value,int vnum,int arcnum,VertexType *ch)
/*�����ڽӾ����ʾ������������N*/
{
	int i,j,k;
	N->vexnum=vnum;
	N->arcnum=arcnum;
	for(i=0;i<vnum;i++)				/*���������㸳ֵ��vex��*/
		strcpy(N->vex[i],ch[i]);
	for(i=0;i<N->vexnum;i++)			/*��ʼ���ڽӾ���*/
		for(j=0;j<N->vexnum;j++)
		{
			N->arc[i][j].adj=INFINITY;
			N->arc[i][j].info=NULL;	/*������Ϣ��ʼ��Ϊ��*/
		}
	for(k=0;k<arcnum;k++)
	{
		i=value[k].row;
		j=value[k].col;
		N->arc[i][j].adj=value[k].weight;
	}

	N->kind=DN;						/*ͼ������Ϊ������*/
}
void DisplayGraph(MGraph N)
/*����ڽӾ���洢��ʾ��ͼN*/
{
	int i,j;
	printf("����������%d������%d����������������: ",N.vexnum,N.arcnum);
	for(i=0;i<N.vexnum;++i)				/*������Ķ���*/
		printf("%s ",N.vex[i]);
	printf("\n������N��:\n");				/*�����N�Ļ�*/
	printf("���i=");
	for(i=0;i<N.vexnum;i++)
		printf("%8d",i);
	printf("\n");
	for(i=0;i<N.vexnum;i++)
	{
		printf("%8d",i);
		for(j=0;j<N.vexnum;j++)
			printf("%8d",N.arc[i][j].adj);
		printf("\n");
	}
}
typedef int PathMatrix[MaxSize][MaxSize];	/*����һ���������·���Ķ�ά����*/
typedef int ShortPathLength[MaxSize];		/*����һ������Ӷ���v0������v����̾��������*/
void Dijkstra (MGraph N,int v0, PathMatrix path,ShortPathLength dist)
/*��Dijkstra�㷨��������N��v0���㵽���������v�����·��path[v]�����·������dist[v]*/
/*final[v]Ϊ1��ʾv��S�����Ѿ������v0��v�����·��*/
{
	int v,w,i,k,min;
	int final[MaxSize];			/*��¼v0���ö�������·���Ƿ������*/
	for(v=0;v<N.vexnum;v++)		/*����dist�洢v0��v����̾��룬��ʼ��Ϊv0��v�Ļ��ľ���*/
	{
		final[v]=0;
		dist[v]=N.arc[v0][v].adj;
		for(w=0;w<N.vexnum;w++)
			path[v][w]=0;
		if(dist[v]<INFINITY)		/*�����v0��v��ֱ��·�������ʼ��·������*/
		{
			path[v][v0]=1;
			path[v][v]=1;
		}
	}
	dist[v0]=0;						/*v0��v0��·��Ϊ0*/
	final[v0]=1;					/*v0���㲢�뼯��S*/
	/*��v0������G.vexnum-1����������·���������ö��㲢�뼯��S*/
	for(i=1;i<N.vexnum;i++)
	{
		min=INFINITY;
		for(w=0;w<N.vexnum;w++)
			if(!final[w]&&dist[w]<min)	/*�ڲ����ڼ���S�Ķ������ҵ���v0����Ķ���*/
			{
				v=w;				    /*������v0����Ķ���w����v������븳��min*/
				min=dist[w];
			}
		final[v]=1;				        /*��v���뼯��S*/
		for(w=0;w<N.vexnum;w++)
             /*�����²��뼯��S�Ķ��㣬����v0�������ڼ���S�Ķ�������·�����Ⱥ����·������*/
		    if(!final[w]&&min<INFINITY&&N.arc[v][w].adj<INFINITY&&(min+N.arc[v][w].adj<dist[w]))
			{
				dist[w]=min+N.arc[v][w].adj;
				for(k=0;k<N.vexnum;k++)
					path[w][k]=path[v][k];
				path[w][w]=1;
			}
	}
}

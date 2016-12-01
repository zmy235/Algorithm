#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;
//最小生成树算法 Minimum Spanning Tree Algorithm MSTA 解决 连通图 问题

//object part
#define pointNumber 20
#define distFT_MAX 1000000
int distFT[pointNumber][pointNumber];
//object part

int RandomIntLessThan(int aint)
{
	return (int) ((double) aint * (double) rand() / (double) (RAND_MAX + 1));
}

int RandomTrueBy(double aprob)
{
	double res = (double) rand() / (RAND_MAX + 1);
	if (res <= aprob)
		return 1;
	else
		return 0;
}

void Prim(int cost[pointNumber][pointNumber],int n,int u)
{
	int lowcost[pointNumber];
	int closest[pointNumber]; //顶点序列   
	int i,j,k,min;
	int whole = 0;

	for(i=0;i<n;i++) //初始处理   
	{   
		lowcost[i]=cost[u][i]; //起始点u到V－U集合中各顶点的权存放在lowcost[]中   
		closest[i]=u; //将从U的各顶点里到达V－U中各顶点权最小的顶点   
	}

	for(i=0;i<n-1;i++) //主循环，若U＝V，则算法结束；否则，从E中选一条代价最小的边(u,v)，并将u加入U中   
		
	{
		min=distFT_MAX;   
		for(j=0;j<n;j++) //用选择排序的概念从lowcost[]中找到U到V－U中代价最小的边   
			if(lowcost[j]!=0&& //该顶点不在U中   
				lowcost[j]<min) //该到顶点边的权比已经找到的权最小的边还要小   
				
			{
				min=lowcost[j];   
				k=j;   
			}
			whole += min;
			cout << "The point is " << k << ", next to " << closest[k] << endl << "The path costs " << min << endl << endl;
		//打印邻接到U中顶点，权最小的边   
		lowcost[k]=0; //将该顶点放入U中，即将lowcost[k]设置为0   
		for(j=0;j<n;j++) //U中加入k后，更新lowcost[]，重新登记最小权   
			if(cost[k][j]!=0&&   
				cost[k][j]<lowcost[j])   
			{   
				lowcost[j]=cost[k][j]; //把从U到V－U中各点权最小的边的权记录下来   
				closest[j]=k; //将到j距离最短距离的顶点更新为k   
			}   
		}
		cout << "The whole cost is " << whole << endl;
	}

	void DisplayMap()
	{
		for (int i = 0; i < pointNumber; i ++)
		{
			for (int j = 0; j < pointNumber; j ++)
			{
				cout << distFT[i][j] << " ";
			}
			cout << endl;
		}
	}

	void main()
	{
		srand((unsigned) time(NULL));
	//object part
		for (int i = 0; i < pointNumber; i ++)
		{
			distFT[i][i] = 0;
			for (int j = i + 1; j < pointNumber; j ++)
			{
				if (RandomTrueBy(0.1))
				{
					distFT[i][j] = distFT_MAX;
				}
				else
					distFT[i][j] = RandomIntLessThan(99) + 1;
			}
		}
		for (i = 0; i < pointNumber; i ++)
		{
			for (int j = 0; j < i; j ++)
			{
				distFT[i][j] = distFT[j][i];
			}
		}
		DisplayMap();
		Prim(distFT, pointNumber, 0);
	//object part
	}
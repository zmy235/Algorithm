#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;
// 动态规划算法 Dynamic Programming Algorithm DPA 解决 全源最短路径
//object part
#define pointNumber 4
#define POINT_MAX 100
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
void main(void)
{
	srand((unsigned) time(NULL));
	//object part
	int cost[POINT_MAX][POINT_MAX];
	for (int i = 0; i < pointNumber; i ++)
	{
		cost[i][i] = 0;
		for (int j = i + 1; j < pointNumber; j ++)
		{
			cost[i][j] = RandomIntLessThan(10) + 1;
		}
	}
	for (i = 0; i < pointNumber; i ++)
	{
		for (int j = 0; j < i; j ++)
		{
			cost[i][j] = cost[j][i];
		}
	}
	//object part
	//求每对结点之间的最短路径
    //cost[][]是成本邻接矩阵
    //int cost[3][3]=
    {
    	{0,4,11},
    {6,0,2},
    {3,200,0}};//输入所求结点图的邻接矩阵,200表示无穷大
	int a[pointNumber][pointNumber];   //存放两点间最短路径矩阵
	int path[pointNumber][pointNumber][pointNumber]=
	{0};//存放结点的路径，初始化
	int j,k;
	for(i=0;i<pointNumber;i++)
	{
		for(j=0;j<pointNumber;j++)
		{
			a[i][j]=cost[i][j];//将cost[i][j]复制到a[i][j]
        }
    }
	for(k=0;k<pointNumber;k++)
	{ //对最高下标为k的结点的路径
			for(i=0;i<pointNumber;i++)
			{ //对于所有可能的结点对
				for(j=0;j<pointNumber;j++)
				{  //求出min
					{a[i][j],a[i][k]+a[k][j]}
					if(a[i][j]>(a[i][k]+a[k][j]))
					{
						a[i][j]=a[i][k]+a[k][j];
						path[i][j][k]=k;//将k结点加入到结点对（i，j）的最短路径中
					}
			   }
			}
		}
	printf("有向图成本邻接矩阵:\n");
    for(i=0;i<=pointNumber;i++)
    {//输出所求结点图的邻接矩阵
        if(i)
        {
            printf("v%d ",i);//打印矩阵的行标v1,v2,……，vn
        }
        for(j=0;j<pointNumber;j++)
        {
            if(!i)
            {
                printf("   v%d",j+1);//打印矩阵的列标
			}
			else
			{
               printf(" %d   ",cost[i-1][j]);
			}
        }
		printf("\n");
    }
	printf("结点对  每对结点之间的最短路径  最短路径值\n");
    for(i=0;i<pointNumber;i++)
    {//输出经算法产生的结点间的最短路径矩阵
		for(j=0;j<pointNumber;j++)
		{
            printf("v%dv%d    ",i+1,j+1);/*打印结点对*/
            printf("v%d    ",i+1);/*打印每对结点之间的最短路径*/
            for(k=0;k<pointNumber;k++)
            {
                if(path[i][j][k])
                {/*打印出已存入的路径*/
                    printf("v%d  ",path[i][j][k]+1);
                }
                else
                {          /*对齐输出格式*/
                    printf("    ");
               }
		}
		printf("v%d  ",j+1);
		printf("    %d    \n\n",a[i][j]);/*打印最短路径值*/}
    }
}
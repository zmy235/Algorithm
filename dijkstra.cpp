#include <iostream>
#include <random>
#include <set>
using namespace std;

#define MAXLINE 10

void initCube(int **tmp)
{
    int *arr[MAXLINE];
    for (int i = 0; i < MAXLINE; ++i)
    {
        arr[i] = tmp[i];
    }
    for (int i = 0; i < MAXLINE; ++i)
    {
        for (int j = 0; j < MAXLINE; ++j)
        {
            arr[i][j] = (i==j)?0:rand()%100;
        }
    }
}

void printPath(int *path,int curentPoint, int startPoint)
{
    int i=curentPoint;
    cout<<"Path:"<<i<<" ";
    while(path[i]!=startPoint)
    {
        cout<<path[i]<<" ";
        i = path[i];
    }
    cout<<startPoint<<endl;
}

int main()
{
    int **tmp = new int*[MAXLINE];
    for (int i = 0; i < MAXLINE; ++i)
    {
        tmp[i] = new int[MAXLINE];
    }
    initCube(tmp);

    for (int i = 0; i < MAXLINE; ++i)
    {
        for (int j = 0; j < MAXLINE; ++j)
        {
            cout<<tmp[i][j]<<" ";
        }
        cout<<endl;
    }

    int startPoint=6;
    cout<<"Start Point:"<<startPoint<<endl;
    set<int> Myset;
    Myset.insert(startPoint);
    int cost[MAXLINE];
    int path[MAXLINE];
    for (int i = 0; i < MAXLINE; ++i)
    {
        cost[i] = 0xFFFF;
    }
    cost[startPoint] = 0;
    path[startPoint] = startPoint;

    for (int c = 1; c < MAXLINE; ++c)
    {
        int sum;
        int minCost = 0xFFFF;
        int min;

        for (int i = 0; i < MAXLINE; ++i)//计算从startPoint到i的距离
        {
            if (Myset.find(i)!=Myset.end())//如果已经在最小集合内，跳过
                continue;
            for (auto j = Myset.begin(); j != Myset.end(); ++j)
            {
                if (cost[*j]+tmp[*j][i]<minCost && (Myset.find(i)==Myset.end()))//判断与当前最小距离的点相比是不是更小
                {
                    min = i;
                    minCost = cost[*j]+tmp[*j][i];
                    path[min] = *j;
                }
            }
        } 
        Myset.insert(min);
        cost[min] = minCost;
        cout<<"Point:"<<min<<" \tCost:"<<minCost<<"\t";
        printPath(path,min,startPoint);
    }
    return 0;
}

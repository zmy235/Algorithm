/*
*快速排序实现及对比
*
*2017-4-10
*
*By veizi
*/

#include<bits/stdc++.h>
using namespace std;
#define SIZE 10
#define RANGE 100

void H(int& i,int& j)
{
    int t;
    t=i,i=j,j=t;
}

int times=0;

//枢轴可移动
void qsort(int* a,int start,int end)
{
    times++;
    int temp=a[start];
    int i = start;
    int j = end;

    while(i<j)
    {
        while( a[j]>=temp && j>i ) j--;
        if( i<j )
        {
            a[i++]=a[j];
            while( a[i]<=temp && i<j ) i++;
            if( i<j ) a[j--]=a[i];
        }
    }
    a[i] = temp;
    if( start<(i-1) ) qsort(a,start,i-1);
    if( (j+1)<end ) qsort(a,j+1,end);
}

//枢轴不移动
void Qsort(int* a,int start,int end)
{
    times++;
    int i = start;
    int j = end;
    int t = start;

    while(i<=j)
    {
        while( i<j && a[i]<=a[start] ) i++;

        if( i==j && a[i]<=a[start])
        {
            t=i;
            break;
        }
        else if(i==j && a[i]>a[start])
        {
            t=j-1;
            break;
        }
        else if(i<j && a[i]>a[start])
        {
            t=i-1;
            while( i<j && a[j]>=a[start] ) j--;
            if(i<j) H(a[i++],a[j--]);
            if(i>j)
            {
                t=i-1;
                break;
            }
        }
    }

    H(a[start],a[t]);

    if(t-1-start>1)Qsort(a,start,t-1);
    if(end-t+1>1)Qsort(a,t+1,end);
}


int main()
{
    //随机数组生成
    int w[SIZE];
    for(int i=0; i<SIZE; i++)
    {
        w[i] = RANGE*rand()/(RAND_MAX + 1);
        cout<<w[i]<<" ";
    }
    cout<<endl;

    //进行排序
    Qsort(w,0,SIZE-1);
    //qsort(w,0,SIZE-1);

    //排序结果
    for(int p=0; p<SIZE; p++) 
        cout<<w[p]<<" ";
    cout<<endl<<times;

    return 0;
}

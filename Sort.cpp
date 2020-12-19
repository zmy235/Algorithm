//*******************************************
//Sort.cpp   
//2014/6/10 by Adaq
//2016/11/1 edited by Veizi
//@brief: 本文件为sort的C++实现。
//*******************************************
#include <iostream>
#include <memory.h>
using namespace std;

class Sort
{
public:
    int leng;
    void Print(int arr[]);

    void Insert(int arr[]); //插入排序
    void Bubble(int arr[]); //冒泡排序
    void Select(int arr[]);  //选择排序
    void Qsort(int arr[],int low,int high);//快速排序
    void Msort(int arr[],int cut[],int s,int t); //归并排序 
    void Merge(int arr[],int cut[],int i,int m,int n);
};

void Sort::Print(int arr[])
{
    cout<<"Rresult: ";
    for(int i=0; i<leng; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

//---------------------------------------------------

void Sort::Insert(int arr[])
{
    for(int i=1; i<leng; i++)
    {
        if(arr[i]<arr[i-1])
        {
            int temp=arr[i];
            for(int j=i-1; temp<arr[j]&&j>=0; j--)
            {
                arr[j+1]=arr[j];
            }
            arr[i+1]=temp;
        }
        Print(arr);
    }
}

//------------------------------------------------------

void Sort::Bubble(int arr[])
{
    for(int i=leng-1; i>=0; i--)
    {
        for(int j=0; j<leng-1; j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
        Print(arr);
    }
}

//------------------------------------------------------------------

void Sort::Select(int arr[])
{
    for(int i=0; i<leng; i++)
    {
        int max=i;
        for(int j=i+1; j<leng; j++)
        {
            if(arr[max]>arr[j]) max=j;
        }
        if(max!=i)
        {
            int temp=arr[max];
            arr[max]=arr[i];
            arr[i]=temp;
        }
        Print(arr);
    }
}

//-----------------------------------------------

void Sort::Qsort(int a[], int low, int high)
{
    if(low >= high) return;
    int first = low;
    int last = high;
    int key = a[first]; /*用字表的第一个记录作为枢轴*/
    while(first < last)
    {
        while(first < last && a[last] >= key) --last;
        a[first] = a[last]; /*将比第一个小的移到低端*/
        while(first < last && a[first] <= key) ++first;
        a[last] = a[first]; /*将比第一个大的移到高端*/
    }
    a[first] = key; /*枢轴记录到位*/
    Qsort(a, low, first-1);
    Print(a);
    Qsort(a, first+1, high);
}

//----------------------------------------------------------

void Sort::Msort(int arr[],int cut[],int s,int t)
{
    if(s==t) cut[s]=arr[s];
    else
    {
        int m=(t+s)/2;
        int n=t-s;
        int *temp = new int[n]();// 每个元素初始化为0
        Msort(arr,temp,s,m);
        Msort(arr,temp,m+1,t);
        Merge(temp,cut,s,m,t);
    }
}

void Sort::Merge(int arr[],int cut[],int i,int m,int n)
{
    int k=i,j=m+1;
    for(; i<=m&&j<=n; k++)
    {
        if(arr[i]<=arr[j]) cut[k]=arr[i++];
        else cut[k]=arr[j++];
    }
    while(i<=m) cut[k++]=arr[i++];
    while(j<=n) cut[k++]=arr[j++];
}

//---------------------------------------------------------

int main()
{
    Sort* S=new Sort();
    int arr[]={5,7,6,8,3,2,9,1};
    S->leng=sizeof(arr)/sizeof(int);
    //S->Insert(arr);
    //S->Bubble(arr);
    //S->Select(arr);
    S->Qsort(arr,0,S->leng-1);
    int *temp = new int[S->leng-1]();// 每个元素初始化为0
    S->Msort(arr,temp,0,S->leng-1);
    return 0;
}

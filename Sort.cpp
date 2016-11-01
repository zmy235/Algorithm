//*******************************************
//Compositor.cpp   2014/6/10 by Adaq
//@brief: 本文件为order的C++实现。
//*******************************************
#include <iostream>
using namespace std;

template<class Type>
class Compositor
{
public:
    void Creat();
    void Print();

    void Bubble(); //冒泡排序

    void Insert(); //插入排序

    void Quick();   //快速排序
    void QSort(int,int);
    int Partition(int low,int high);

    void Merge(Type SR[],Type TR[],int i,int m,int n);  //归并排序
    void Msort(Type SR[],Type TR1[],int s,int t);
    void MergeSort();

    void Select();  //选择排序

protected:
    Type *sort;
    int leng;
};


template<class Type>
void Compositor<Type>::Creat()
{
    cout<<"Put in the number you want to order:";
    cin>>leng;
    sort=new Type[leng];
    cout<<"Put In your data:";
    for(int i=0; i<leng; i++)
        cin>>sort[i];
}

template<class Type>
void Compositor<Type>::Print()
{
    cout<<"Rresult: ";
    for(int i=0; i<leng; i++)
        cout<<sort[i]<<" ";
    cout<<endl;
}

//---------------------------------------------------

template<class Type>
void Compositor<Type>::Insert()
{
    Type temp;
    for(int i=1; i<leng; i++)
    {
        if(sort[i]<sort[i-1])
        {
            temp=sort[i];
            for(int j=i-1; temp<sort[j]&&j>=0; j--)
            {
                sort[j+1]=sort[j];
            }
            sort[i+1]=temp;
        }
    Print();
    }
}

//------------------------------------------------------

template<class Type>
void Compositor<Type>::Bubble()
{
    Type temp;
    for(int i=leng-1; i>=0; i--)
    {
        for(int j=0; j<leng-1; j++)
        {
            if(sort[j]>sort[j+1])
            {
                temp=sort[j];
                sort[j]=sort[j+1];
                sort[j+1]=temp;
            }
        }
    Print();
    }
}

//-----------------------------------------------

template<class Type>
void Compositor<Type>::Quick()
{
    QSort(0,leng-1);
}

template<class Type>
void Compositor<Type>::QSort(int s,int t)
{
    if(s<t-1)
    {
        int pivotloc=Partition(s,t);
        QSort(s,pivotloc-1);
        QSort(pivotloc+1,t);
    }
    Print();
}

template<class Type>
int Compositor<Type>::Partition(int low,int high)
{
    Type pivotkey=sort[low];
    while(low < high)
    {
        while(low<high&&sort[high]>=pivotkey)
            --high;
        sort[low++]=sort[high];
        while(low<high&&sort[low]<=pivotkey)
            ++low;
        sort[high--]=sort[low];
    }
    sort[low]=pivotkey;
    return low;
}

//----------------------------------------------------------

template<class Type>
void Compositor<Type>::MergeSort()
{
    Msort(sort,sort,0,leng-1);
    Print();
}

template<class Type>
void Compositor<Type>::Msort(Type SR[],Type TR1[],int s,int t)
{
    int m;
    Type *TR2=new Type[t-s];
    if(s==t) TR1[s]=SR[s];
    else
    {
        m=(t+s)/2;
        Msort(SR,TR2,s,m);
        Msort(SR,TR2,m+1,t);
        Merge(TR2,TR1,s,m,t);
    }
}

template<class Type>
void Compositor<Type>::Merge(Type SR[],Type TR[],int i,int m,int n)
{
    int j=m+1;
    int k=i;
    for(; i<=m&&j<=n; k++)
    {
        if(SR[i]<=SR[j])
            TR[k]=SR[i++];
        else
            TR[k]=SR[j++];
    }
    while(i<=m)
        TR[k++]=SR[i++];
    while(j<=n)
        TR[k++]=SR[j++];
}

//------------------------------------------------------------------

template<class Type>
void Compositor<Type>::Select()
{
    Type temp;
    int t;
    for(int i=0; i<leng; i++)
    {
        t=i;
        for(int j=i+1; j<leng; j++)
        {
            if(sort[t]>sort[j])
                t=j;
        }
        if(t!=i)
        {
            temp=sort[t];
            sort[t]=sort[i];
            sort[i]=temp;
        }
    Print();
    }
}

//---------------------------------------------------------

int main()
{
    typedef int type;
    Compositor <type> Compositor1;
    for(;;)
    {
        cout<<"Make Your Choice:"<<endl
            <<" 0) Array"<<endl
            <<" 1) Insert"<<endl
            <<" 2) Quick"<<endl
            <<" 3) Merge"<<endl
            <<" 4) Bubble"<<endl
            <<" 5) Select"<<endl;
        int item;
        cin>>item;
        switch(item)
        {
        case 0:
            Compositor1.Creat();
            break;
        case 1:
            Compositor1.Insert();
            break;
        case 2:
            Compositor1.Quick();
            break;
        case 3:
            Compositor1.MergeSort();
            break;
        case 4:
            Compositor1.Bubble();
            break;
        case 5:
            Compositor1.Select();
            break;
        default:
            break;
        }
    }
    return 0;
}

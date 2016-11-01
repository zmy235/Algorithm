/*贪心算法求解0-1背包问题

贪心法的基本思路：
从问题的某一个初始解出发逐步逼近给定的目标，
以尽可能快的地求得更好的解。
当达到某算法中的某一步不能再继续前进时，算法停止。

该算法存在问题：
1).不能保证求得的最后解是最佳的；
2).不能用来求最大或最小解问题；
3).只能求满足某些约束条件的可行解的范围。

实现该算法的过程：
从问题的某一初始解出发；
while 能朝给定总目标前进一步 do
    　　 求出可行解的一个解元素；
    由所有解元素组合成问题的一个可行解；

例题分析:
            有一个背包，背包容量是M=150。有7个物品，物品可以分割成任意大小。
            要求尽可能让装入背包中的物品总价值最大，但不能超过总容量。

            物品 A B C D E F G
            重量 35 30 60 50 40 10 25
            价值 10 40 30 50 35 40 30

            分析：
            目标函数： ∑pi最大
            约束条件是装入的物品总重量不超过背包容量：∑wi<=M( M=150)
            （1）根据贪心的策略，每次挑选价值最大的物品装入背包，得到的结果是否最优？
            （2）每次挑选所占空间最小的物品装入是否能得到最优解？
            （3）每次选取单位容量价值最大的物品，成为解本题的策略。
        */

#include<iostream>
#define max 100 //最多物品数
using namespace std;

void sort (int n,float a[max],float b[max]) //按价值密度排序
{
    int j,h,k;
    float t1,t2,t3,c[max];
    for(k=1; k<=n; k++)
        c[k]=a[k]/b[k];
    for(h=1; h<n; h++)
        for(j=1; j<=n-h; j++)
            if(c[j]<c[j+1])
            {
                t1=a[j];
                a[j]=a[j+1];
                a[j+1]=t1;
                t2=b[j];
                b[j]=b[j+1];
                b[j+1]=t2;
                t3=c[j];
                c[j]=c[j+1];
                c[j+1]=t3;
            }
}

void knapsack(int n,float limitw,float v[max],float w[max],int x[max])
{
    float c1; //c1为背包剩余可装载重量
    int i;
    sort(n,v,w); //物品按价值密度排序
    c1=limitw;
    for(i=1; i<=n; i++)
    {
        if(w[i]>c1)break;
        x[i]=1; //x[i]为1时，物品i在解中
        c1=c1-w[i];
    }
}

int main()
{
    int n,i,x[max];
    float v[max],w[max],totalv=0,totalw=0,limitw;


    cout<<"请输入n和limitw:";
    cin>>n >>limitw;
    for(i=1; i<=n; i++)
        x[i]=0; //物品选择情况表初始化为0
    cout<<"请依次输入物品的价值："<<endl;
    for(i=1; i<=n; i++)
        cin>>v[i];
    cout<<endl;
    cout<<"请依次输入物品的重量："<<endl;
    for(i=1; i<=n; i++)
        cin>>w[i];
    cout<<endl;


    knapsack (n,limitw,v,w,x);
    cout<<"the selection is:";
    for(i=1; i<=n; i++)
    {
        cout<<x[i];
        if(x[i]==1)
            totalw=totalw+w[i];
    }
    cout<<endl;
    cout<<"背包的总重量为："<<totalw<<endl; //背包所装载总重量
    cout<<"背包的总价值为："<<totalv<<endl; //背包的总价值
}

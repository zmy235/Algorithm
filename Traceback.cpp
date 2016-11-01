/*
回溯算法求解0-1背包问题

一般情况下，0-1背包问题是NP难题。
0-1背包问题的解空间可用子集树表示。

在搜索解空间树时，只要其左儿子结点是一个可行结点，搜索就进入其左子树。
当右子树有可能包含最优解时才进入右子树搜索。否则将右子树剪去。
设r是当前剩余物品价值总和；cp是当前价值；bestp是当前最优价值。
当cp+r≤bestp时，可剪去右子树。

计算右子树中解的上界的更好方法是将剩余物品依其单位重量价值排序，
然后依次装入物品，直至装不下时，再装入该物品的一部分而装满背包。
由此得到的价值是右子树中解的上界。

2.解决办法思路：
为了便于计算上界，可先将物品依其单位重量价值从大到小排序，此后只要顺序考
察各物品即可。在实现时，由bound计算当前结点处的上界。在搜索解空间树时，
只要其左儿子节点是一个可行结点，搜索就进入左子树，在右子树中有可能包含最优解是才进入右子树搜索。
否则将右子树剪去。

回溯法是一个既带有系统性又带有跳跃性的的搜索算法。
它在包含问题的所有解的解空间树中，按照深度优先的策略，从根结点出发搜索解空间树。
算法搜索至解空间树的任一结点时，总是先判断该结点是否肯定不包含问题的解。
如果肯定不包含，则跳过对以该结点为根的子树的系统搜索，逐层向其祖先结点回溯。
否则，进入该子树，继续按深度优先的策略进行搜索。
回溯法在用来求问题的所有解时，要回溯到根，且根结点的所有子树都已被搜索遍才结束。
而回溯法在用来求问题的任一解时，只要搜索到问题的一个解就可以结束。
这种以深度优先的方式系统地搜索问题的解的算法称为回溯法，它适用于解一些组合数较大的问题。

2.算法框架：

a.问题的解空间：
应用回溯法解问题时，首先应明确定义问题的解空间。
问题的解空间应到少包含问题的一个（最优）解。

b.回溯法的基本思想：
确定了解空间的组织结构后，回溯法就从开始结点（根结点）出发，以深度优先的方式搜索整个解空间。
这个开始结点就成为一个活结点，同时也成为当前的扩展结点。
在当前的扩展结点处，搜索向纵深方向移至一个新结点。
这个新结点就成为一个新的活结点，并成为当前扩展结点。
如果在当前的扩展结点处不能再向纵深方向移动，则当前扩展结点就成为死结点。
换句话说，这个结点不再是一个活结点。
此时，应往回移动（回溯）至最近的一个活结点处，并使这个活结点成为当前的扩展结点。
回溯法即以这种工作方式递归地在解空间中搜索，直至找到所要求的解或解空间中已没有活结点时为止。

3.运用回溯法解题通常包含以下三个步骤：
a.针对所给问题，定义问题的解空间；
b.确定易于搜索的解空间结构；
c.以深度优先的方式搜索解空间，并且在搜索过程中用剪枝函数避免无效搜索；
*/
#include<iostream>
using namespace std;

class Knap
{
    friend int Knapsack(int p[],int w[],int c,int n );

public:
    void print()
    {

        for(int m=1; m<=n; m++)
        {
            cout<<bestx[m]<<" ";
        }
        cout<<endl;
    };

private:
    int Bound(int i);
    void Backtrack(int i);

    int c;//背包容量
    int n; //物品数
    int *w;//物品重量数组
    int *p;//物品价值数组
    int cw;//当前重量
    int cp;//当前价值
    int bestp;//当前最优值
    int *bestx;//当前最优解
    int *x;//当前解

};

//-----------------------------------------------------------------

int Knap::Bound(int i)
{
//计算上界
    int cleft=c-cw;//剩余容量
    int b=cp;
//以物品单位重量价值递减序装入物品
    while(i<=n&&w[i]<=cleft)
    {
        cleft-=w[i];
        b+=p[i];
        i++;
    }
//装满背包
    if(i<=n)
        b+=p[i]/w[i]*cleft;
    return b;
}

//-----------------------------------------------------------------

void Knap::Backtrack(int i)
{
    if(i>n)
    {
        if(bestp<cp)
        {
            for(int j=1; j<=n; j++)
                bestx[j]=x[j];
            bestp=cp;
        }
        return;
    }

    if(cw+w[i]<=c) //搜索左子树
    {
        x[i]=1;
        cw+=w[i];
        cp+=p[i];
        Backtrack(i+1);
        cw-=w[i];
        cp-=p[i];
    }

    if(Bound(i+1)>bestp)//搜索右子树
    {
        x[i]=0;
        Backtrack(i+1);
    }

}

//-----------------------------------------------------------------

class Object
{
    friend int Knapsack(int p[],int w[],int c,int n);
public:
    int operator<=(Object a)const
    {
        return (d>=a.d);
    }

private:
    int ID;
    float d;
};

//-----------------------------------------------------------------

int Knapsack(int p[],int w[],int c,int n)
{
//为Knap::Backtrack初始化
    int W=0;
    int P=0;
    int i=1;
    Object *Q=new Object[n];
    for(i=1; i<=n; i++)
    {
        Q[i-1].ID=i;
        Q[i-1].d=1.0*p[i]/w[i];
        P+=p[i];
        W+=w[i];
    }
    if(W<=c)
        return P;
//装入所有物品
//依物品单位重量排序
    float f;
    for( i=0; i<n; i++)
        for(int j=i; j<n; j++)
        {
            if(Q[i].d<Q[j].d)
            {
                f=Q[i].d;
                Q[i].d=Q[j].d;
                Q[j].d=f;
            }

        }

    Knap K;
    K.p = new int[n+1];
    K.w = new int[n+1];
    K.x = new int[n+1];
    K.bestx = new int[n+1];
    K.x[0]=0;
    K.bestx[0]=0;
    for( i=1; i<=n; i++)
    {
        K.p[i]=p[Q[i-1].ID];
        K.w[i]=w[Q[i-1].ID];
    }
    K.cp=0;
    K.cw=0;
    K.c=c;
    K.n=n;
    K.bestp=0;
//回溯搜索
    K.Backtrack(1);
    K.print();
    delete [] Q;
    delete [] K.w;
    delete [] K.p;
    return K.bestp;

}

//-----------------------------------------------------------------

int main()
{
    int *p;
    int *w;
    int c=0;
    int n=0;
    int i=0;
    char k;

    while(k)
    {
        cout<<"请输入背包容量(c)："<<endl;
        cin>>c;
        cout<<"请输入物品的个数(n)："<<endl;
        cin>>n;
        p=new int[n+1];
        w=new int[n+1];
        p[0]=0;
        w[0]=0;

        cout<<"请输入物品的价值(p)："<<endl;
        for(i=1; i<=n; i++)
            cin>>p[i];

        cout<<"请输入物品的重量(w)："<<endl;
        for(i=1; i<=n; i++)
            cin>>w[i];

        cout<<"最优解为(bestx)："<<endl;
        cout<<"最优值为(bestp)："<<endl;
        cout<<Knapsack(p,w,c,n)<<endl;
        cout<<"[s] 重新开始"<<endl;
        cout<<"[q] 退出"<<endl;
        cin>>k;
    }
    return 0;
}

/*

    分支限界法

    1.问题描述：
    已知有N个物品和一个可以容纳M重量的背包，
    每种物品I的重量为WEIGHT，一个只能全放入或者不放入，
    求解如何放入物品，可以使背包里的物品的总效益最大。

    2.设计思想与分析：
    对物品的选取与否构成一棵解树，
    左子树表示不装入，右表示装入，通过检索问题的解树得出最优解，
    并用结点上界杀死不符合要求的结点。

 */
#include <iostream>
using namespace std;
struct good
{
    int weight;
    int benefit;
    int flag;//是否可以装入标记
};

int number=0;//物品数量
int upbound=0;
int curp=0, curw=0;//当前效益值与重量
int maxweight=0;
good *bag=NULL;

void Init_good()
{
    bag=new good [number];

    for(int i=0; i<number; i++)
    {
        cout<<"请输入第件"<<i+1<<"物品的重量:";
        cin>>bag[i].weight;
        cout<<"请输入第件"<<i+1<<"物品的效益:";
        cin>>bag[i].benefit;
        bag[i].flag=0;//初始标志为不装入背包
        cout<<endl;
    }

}

int getbound(int num, int *bound_u)//返回本结点的c限界和u限界
{
    int w,p;
    for(int w=curw, p=curp; num<number && (w+bag[num].weight)<=maxweight; num++)
    {
        w=w+bag[num].weight;
        p=w+bag[num].benefit;
    }

    *bound_u=p+bag[num].benefit;
    return ( p+bag[num].benefit*((maxweight-w)/bag[num].weight) );
}

void LCbag()
{
    int bound_u=0, bound_c=0;//当前结点的c限界和u限界

    for(int i=0; i<number; i++)//逐层遍历解树决定是否装入各个物品
    {
        if( ( bound_c=getbound(i+1, &bound_u) )>upbound )//遍历左子树
            upbound=bound_u;//更改已有u限界,不更改标志

        if( getbound(i, &bound_u)>bound_c )//遍历右子树
//若装入，判断右子树的c限界是否大于左子树根的c限界，是则装入
        {
            upbound=bound_u;//更改已有u限界
            curp=curp+bag[i].benefit;
            curw=curw+bag[i].weight;//从已有重量和效益加上新物品
            bag[i].flag=1;//标记为装入
        }
    }

}

void Display()
{
    cout<<"可以放入背包的物品的编号为：";
    for(int i=0; i<number; i++)
        if(bag[i].flag>0)
            cout<<i+1<<" ";
    cout<<endl;
    delete []bag;
}

int main()
{
    Init_good();
    LCbag();
    Display();

    return 0;
}

/* 0-1背包问题：
    给定n种物品和一个背包,物品i的重量为wi,其价值为vi,背包的容量为c
    应如何选择装入背包的物品，使得装入背包中的物品的总价值最大？

  形式化描述：
    给定c>0, wi>0, vi>0, 0<=i<=n，要求找到一个n元的
    0-1向量(x1, x2, ..., xn), 使得：
            max sum_{i=1 to n} (vi*xi),且满足如下约束：
        (1) sum_{i=1 to n} (wi*xi) <= c
        (2) xi∈{0, 1}, 1<=i<=n

  问题的求解:
    0-1背包问题具有最优子结构性质和子问题重叠性质，适于
    采用动态规划方法求解

  最优子结构性质:
    设(y1,y2,...,yn)是给定0-1背包问题的一个最优解，则必有
    结论，(y2,y3,...,yn)是如下子问题的一个最优解：
            max sum_{i=2 to n} (vi*xi)
        (1) sum_{i=2 to n} (wi*xi) <= c - w1*y1
        (2) xi∈{0, 1}, 2<=i<=n
    因为如若不然，则该子问题存在一个最优解(z2,z3,...,zn)，而(y2,y3,...,yn)不是其最优解。
    那么有：
        sum_{i=2 to n} (vi*zi) > sum_{i=2 to n} (vi*yi)
        且，w1*y1 + sum_{i=2 to n} (wi*zi) <= c
    进一步有：
        v1*y1 + sum_{i=2 to n} (vi*zi) > sum_{i=1 to n} (vi*yi)
        w1*y1 + sum_{i=2 to n} (wi*zi) <= c
    这说明：(y1,z2,z3,...zn)是所给0-1背包问题的更优解，那么
    说明(y1,y2,...,yn)不是问题的最优解，与前提矛盾，所以最优
    子结构性质成立。

  子问题重叠性质:
    设所给0-1背包问题的子问题 P(i,j)为：
            max sum_{k=i to n} (vk*xk)
        (1) sum_{k=i to n} (wk*xk) <= j
        (2) xk∈{0, 1}, i<=k<=n
    问题P(i,j)是背包容量为j、可选物品为i,i+1,...,n时的子问题
    设m(i,j)是子问题P(i,j)的最优值，即最大总价值。则根据最优
    子结构性质，可以建立m(i,j)的递归式：
        a. 递归初始 m(n,j)
        //背包容量为j、可选物品只有n，若背包容量j大于物品n的
        //重量，则直接装入；否则无法装入。
            m(n,j) = vn, j>=wn
            m(n,j) = 0, 0<=j<wn
        b. 递归式 m(i,j)
        //背包容量为j、可选物品为i,i+1,...,n
        //如果背包容量j<wi，则根本装不进物品i，所以有：
            m(i,j) = m(i+1,j), 0<=j<wi
        //如果j>=wi，则在不装物品i和装入物品i之间做出选择
            不装物品i的最优值：m(i+1,j)
            装入物品i的最优值：m(i+1, j-wi) + vi
            所以：
            m(i,j) = max {m(i+1,j), m(i+1, j-wi) + vi}, j>=wi

*/
#include<iostream>
using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

void Knapsack(int* v, int *w, int c, int n, int **m)
{
    //递归初始条件
    int j, jMax = min(w[n] - 1, c);

    for (j=0; j<=jMax; j++)
    {
        m[n][j] = 0;
    }

    for (j=w[n]; j<=c; j++)
    {
        m[n][j] = v[n];
    }

    //i从2到n-1，分别对j>=wi和0<=j<wi即使m(i,j)
    for (int i=n-1; i>1; i--)
    {
        jMax = min(w[i] - 1, c);
        for (int j=0; j<=jMax; j++)
        {
            m[i][j] = m[i+1][j];
        }
        for (j=w[i]; j<=c; j++)
        {
            m[i][j] = max(m[i+1][j], m[i+1][j-w[i]]+v[i]);
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }

    m[1][c] = m[2][c];

    if (c >= w[1])
    {
        m[1][c] = max(m[1][c], m[2][c-w[1]]+v[1]);
        cout<<m[1][c]<<" ";
    }

}

void TraceBack(int **m, int *w, int c, int n, int* x)
{
    for (int i=1; i<n; i++)
    {
        if(m[i][c] == m[i+1][c])
        {
            x[i] = 0;
        }
        else
        {
            x[i] = 1;
            c -= w[i];
        }
    }
    x[n] = (m[n][c])? 1:0;
}

int main()
{
    int n = 5;
    int w[6] = {-1, 2, 2, 6, 5, 4};
    int v[6] = {-1, 6, 3, 5, 4, 6};
    int c = 10;

    int **ppm = new int*[n+1];
    for (int i=0; i<n+1; i++)
    {
        ppm[i] = new int[c+1];
    }

    int x[6];

    Knapsack(v, w, c, n, ppm);
    TraceBack(ppm, w, c, n, x);

    return 0;
}

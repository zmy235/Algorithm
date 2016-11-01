/* 0-1�������⣺
    ����n����Ʒ��һ������,��Ʒi������Ϊwi,���ֵΪvi,����������Ϊc
    Ӧ���ѡ��װ�뱳������Ʒ��ʹ��װ�뱳���е���Ʒ���ܼ�ֵ���

  ��ʽ��������
    ����c>0, wi>0, vi>0, 0<=i<=n��Ҫ���ҵ�һ��nԪ��
    0-1����(x1, x2, ..., xn), ʹ�ã�
            max sum_{i=1 to n} (vi*xi),����������Լ����
        (1) sum_{i=1 to n} (wi*xi) <= c
        (2) xi��{0, 1}, 1<=i<=n

  ��������:
    0-1����������������ӽṹ���ʺ��������ص����ʣ�����
    ���ö�̬�滮�������

  �����ӽṹ����:
    ��(y1,y2,...,yn)�Ǹ���0-1���������һ�����Ž⣬�����
    ���ۣ�(y2,y3,...,yn)�������������һ�����Ž⣺
            max sum_{i=2 to n} (vi*xi)
        (1) sum_{i=2 to n} (wi*xi) <= c - w1*y1
        (2) xi��{0, 1}, 2<=i<=n
    ��Ϊ������Ȼ��������������һ�����Ž�(z2,z3,...,zn)����(y2,y3,...,yn)���������Ž⡣
    ��ô�У�
        sum_{i=2 to n} (vi*zi) > sum_{i=2 to n} (vi*yi)
        �ң�w1*y1 + sum_{i=2 to n} (wi*zi) <= c
    ��һ���У�
        v1*y1 + sum_{i=2 to n} (vi*zi) > sum_{i=1 to n} (vi*yi)
        w1*y1 + sum_{i=2 to n} (wi*zi) <= c
    ��˵����(y1,z2,z3,...zn)������0-1��������ĸ��Ž⣬��ô
    ˵��(y1,y2,...,yn)������������Ž⣬��ǰ��ì�ܣ���������
    �ӽṹ���ʳ�����

  �������ص�����:
    ������0-1��������������� P(i,j)Ϊ��
            max sum_{k=i to n} (vk*xk)
        (1) sum_{k=i to n} (wk*xk) <= j
        (2) xk��{0, 1}, i<=k<=n
    ����P(i,j)�Ǳ�������Ϊj����ѡ��ƷΪi,i+1,...,nʱ��������
    ��m(i,j)��������P(i,j)������ֵ��������ܼ�ֵ�����������
    �ӽṹ���ʣ����Խ���m(i,j)�ĵݹ�ʽ��
        a. �ݹ��ʼ m(n,j)
        //��������Ϊj����ѡ��Ʒֻ��n������������j������Ʒn��
        //��������ֱ��װ�룻�����޷�װ�롣
            m(n,j) = vn, j>=wn
            m(n,j) = 0, 0<=j<wn
        b. �ݹ�ʽ m(i,j)
        //��������Ϊj����ѡ��ƷΪi,i+1,...,n
        //�����������j<wi�������װ������Ʒi�������У�
            m(i,j) = m(i+1,j), 0<=j<wi
        //���j>=wi�����ڲ�װ��Ʒi��װ����Ʒi֮������ѡ��
            ��װ��Ʒi������ֵ��m(i+1,j)
            װ����Ʒi������ֵ��m(i+1, j-wi) + vi
            ���ԣ�
            m(i,j) = max {m(i+1,j), m(i+1, j-wi) + vi}, j>=wi

*/
#include<iostream>
using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

void Knapsack(int* v, int *w, int c, int n, int **m)
{
    //�ݹ��ʼ����
    int j, jMax = min(w[n] - 1, c);

    for (j=0; j<=jMax; j++)
    {
        m[n][j] = 0;
    }

    for (j=w[n]; j<=c; j++)
    {
        m[n][j] = v[n];
    }

    //i��2��n-1���ֱ��j>=wi��0<=j<wi��ʹm(i,j)
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

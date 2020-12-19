#include <iostream>
#include <random>
using namespace std;

#define MAXLINE 5

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
            arr[i][j] = rand()%10;
        }
    }
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

    cout<<"Put in the Start Point:";
    int startPoint;
    cin>>startPoint;

    int sum=0;
    for (int i = 0; i < count; ++i)
    {
        /* code */
    }




    return 0;
}

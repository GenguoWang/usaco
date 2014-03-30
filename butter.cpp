/*
ID: wanggen3
PROG: butter
LANG: C++
*/
#include <iostream>
#include <fstream>
#define MAX 99999999
using namespace std;
ifstream fin("butter.in");
ofstream fout("butter.out");
int main(int argv,char*argc[])
{
    int N,P,C;
    int cow[500];
    int path[800][800];
    int x,y,w;
    fin >> N >> P >> C;
    for(int i=0;i<N;++i)fin>>cow[i];
    for(int i=0;i<P;++i)
    {
        for(int j=0;j<P;++j)
        {
            if(i!=j)path[i][j] = MAX;
            else path[i][j] = 0;
        }
    }
    for(int i=0;i<C;++i)
    {
        fin >> x >> y >> w;
        path[x-1][y-1] = w;
        path[y-1][x-1] = w;
    }
    for(int i=0;i<P;++i)
    {
        for(int j=0;j<P;++j)
        {
            for(int k=0;k<P;++k)
            {
                if(path[j][i]+path[i][k]<path[j][k])
                    path[j][k] = path[j][i]+path[i][k];
            }
        }
    }
    int minCost = MAX,currentCost;
    int minP;
    for(int i=0;i<P;++i)
    {
        currentCost = 0;
        for(int j=0;j<N;++j)
        {
            currentCost += path[cow[j]-1][i];
        }
        if(currentCost<minCost)
        {
            minCost = currentCost;
            minP = i;
        }
    }
    fout << minCost << endl;
    fin.close();
    fout.close();
    return 0;
}

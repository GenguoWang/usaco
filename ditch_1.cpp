/*
ID: wanggen3
PROG: ditch
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;
ifstream fin("ditch.in");
ofstream fout("ditch.out");
int flowMap[201][201];
int pre[201];
int M,N;
int getAugment(int s,int t)
{
    memset((void*)pre,0,sizeof(pre));
    pre[s] = -1;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int n = q.front();q.pop();
        for(int i=1;i<=M;++i)
        {
            if(pre[i]==0 && flowMap[n][i]>0)
            {
                pre[i] = n;
                q.push(i);
                if(i==t) break;
            }
        }
    }
    if(pre[t]==0) return 0;
    int flow = 0x1fffffff;
    for(int n=t;pre[n]>0;n = pre[n])
    {
        flow = min(flow,flowMap[pre[n]][n]);
    }
    for(int n=t;pre[n]>0;n = pre[n])
    {
        flowMap[pre[n]][n] -= flow;
        flowMap[n][pre[n]] += flow;
    }
    return flow;
}
int maxFlow(int s,int t)
{
    int sum=0,u;
    while((u = getAugment(s,t))>0)
    {
        sum += u;
    }
    return sum;
}
int main(int argv,char*argc[])
{
    fin >> N >> M;
    int x,y,w;
    while(N--)
    {
        fin >> x >> y >> w;
        flowMap[x][y] += w;
    }
    fout << maxFlow(1,M) << endl;
    fin.close();
    fout.close();
    return 0;
}

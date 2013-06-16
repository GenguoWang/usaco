/*
ID: wanggen3
PROG: concom
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <vector>
using namespace std;
int pct[101][101];
int tot[101][101];
vector<int> node[101];
set<int> own[101];
int abl[101];
int start;
void dfs(int s)
{
    for(vector<int>::iterator it=node[s].begin();it!=node[s].end();++it)
    {
        int i=*it;
        if(abl[i]) continue;
        tot[start][i] += pct[s][i];
        if(tot[start][i] > 50)
        {
            abl[i] = 1;
            own[start].insert(i);
            dfs(i);
        }
    }
}
int main(int argv,char*argc[])
{
    memset((void*)pct,0,sizeof(int)*101*101);
    memset((void*)tot,0,sizeof(int)*101*101);
    freopen("concom.in", "r", stdin);
    freopen("concom.out", "w", stdout);
    int n,t1,t2,t3;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d%d%d",&t1,&t2,&t3);
        pct[t1][t2] = t3;
        node[t1].push_back(t2);
    }
    for(int i=1;i<=100;++i)
    {
        memset((void*)abl,0,sizeof(int)*101);
        abl[i] = 1;
        start = i;
        dfs(start);
    }
    for(int i=1;i<=100;++i)
    {
        for(set<int>::iterator it=own[i].begin();it!=own[i].end();++it)
        {
            if(i!=*it) printf("%d %d\n",i,*it); 
        }
    }
    return 0;
}

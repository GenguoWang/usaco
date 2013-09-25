/*
ID: wanggen3
PROG: concom
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
using namespace std;
ifstream fin("concom.in");
ofstream fout("concom.out");
int main(int argv,char*argc[])
{
    int pct[101][101];
    set<int> own[101];
    memset((void*)pct,0,sizeof(int)*101*101);
    int n,t1,t2,tot;
    fin >> n;
    for(int i=0;i<n;++i)
    {
        fin >> t1 >> t2;
        fin >> pct[t1][t2];
    }
    for(int i=1;i<=100;++i) own[i].insert(i);
    bool flag=true;
    while(flag)
    {
        flag = false;
        for(int i=1;i<=100;++i)
        {
            for(int j=1;j<=100;++j)
            {
                if(own[i].count(j)!=0)continue;
                tot = 0;
                for(set<int>::iterator it=own[i].begin();it!=own[i].end();++it)
                {
                   tot += pct[*it][j]; 
                }
                if(tot > 50) {own[i].insert(j);flag=true;}
            }
        }
    }
    for(int i=1;i<=100;++i)
    {
        for(set<int>::iterator it=own[i].begin();it!=own[i].end();++it)
        {
            if(i!=*it)fout << i <<" " << *it << "\n";
        }
    }
    fin.close();
    fout.close();
    return 0;
}

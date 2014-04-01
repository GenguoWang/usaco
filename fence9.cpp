/*
ID: wanggen3
PROG: fence9
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("fence9.in");
ofstream fout("fence9.out");
int main(int argv,char*argc[])
{
    long long n,m,p;
    fin >> m >> n >>p;
    long long res=0;
    for(int i=1; i < m;++i)
    {
        res += i*n/m;
        if(i*n%m==0) res--;
    }
    if(p>m)
    {
        for(int i=m;i<p;++i)
        {
            if(i==0) continue;
            res += (p-i)*n/(p-m);
            if((p-i)*n%(p-m)==0)res--;
        }
    }
    if(p<m)
    {
        for(int i=p+1;i<m;++i)
        {
            res -= (i-p)*n/(m-p);
        }
    }
    fout << res << '\n';
    fin.close();
    fout.close();
    return 0;
}

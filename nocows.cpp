/*
ID: wanggen3
PROG: nocows
LANG: C++
*/
#include <iostream>
#include <fstream>
#define MOD 9901
using namespace std;
ifstream fin("nocows.in");
ofstream fout("nocows.out");
bool abl[201][101];
int v[201][101];
int f(int n,int k)
{
    if(k==1)
    {
        if(n==1) return 1;
        else return 0;
    }
    if(k==2)
    {
        if(n==3) return 1;
        else return 0;
    }
    if(abl[n][k]) return v[n][k];
    int res = 0;
    int l,r,lsum,rsum;
    for(int i = 1; i < n; i+=2)
    {
        l = i; r = n-1-i; 
        lsum=0;rsum=0;
        for(int j=1; j <= k-2; ++j)
        {
            lsum += f(l,j);
            rsum += f(r,j);
        }
        lsum %= MOD;
        rsum %= MOD;
        res = (res+lsum*f(r,k-1)+f(l,k-1)*rsum+f(l,k-1)*f(r,k-1))%MOD;
    }
    abl[n][k] = 1;
    v[n][k] = res;
    return res;
}
int main(int argv,char*argc[])
{
    int n,k;
    fin >> n >> k;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=k;++j)
            abl[i][j]=0;
    fout << f(n,k) << endl;
    fin.close();
    fout.close();
    return 0;
}

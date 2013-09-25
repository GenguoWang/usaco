/*
ID: wanggen3
PROG: money
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("money.in");
ofstream fout("money.out");
int main(int argv,char*argc[])
{
    unsigned long long val[10001][2];
    int w[26];
    int n,v;
    fin >> v >> n;
    for(int i=1; i <= v;++i) fin>>w[i];
    for(int i=0; i <= n; ++i) val[i][0]=val[i][1]=0;
    val[0][0] = 1;
    int pre,now;
    for(int i=1;i <= v;++i)
    {
        pre = (i-1)%2;
        now = i%2;
        for(int j=0;j<=n;++j)
        {
            val[j][now] = 0;
            for(int k=0;k<=j;k+=w[i])
            {
                val[j][now]+=val[j-k][pre];
            }
        }
    }
    fout << val[n][v%2] << endl;
    fin.close();
    fout.close();
    return 0;
}

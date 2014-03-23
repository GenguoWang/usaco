/*
ID: wanggen3
PROG: kimbits
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
ifstream fin("kimbits.in");
ofstream fout("kimbits.out");
unsigned f[32][32];
int main(int argv,char*argc[])
{
    unsigned int N,L,I;
    fin >> N >> L >> I;
    for(int n=1; n <= N; ++n)
    {
        for(int i=0; i <= L; ++i)
        {
            if(i==0) f[n][i] = 1;
            else if(i>=n) f[n][i] = 1 << n;
            else f[n][i] = f[n-1][i-1]+f[n-1][i];
        }
    }
    int size = N;
    string res(N,'0');
    while(N>1)
    {
        while(f[N-1][L]>=I&&N>1)
        {
            N--;
        }
        if(N>1)
        {
            res[size-N] = '1';
            I -= f[N-1][L];
            L--;
        }
    }
    if(I>1) res[size-N]='1';
    fout << res << endl;
    fin.close();
    fout.close();
    return 0;
}

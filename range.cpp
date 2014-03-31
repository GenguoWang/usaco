/*
ID: wanggen3
PROG: range
LANG: C++
*/
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
ifstream fin("range.in");
ofstream fout("range.out");
int main(int argv,char*argc[])
{
    char range[250][250];
    int state[250][250];
    int res[251];
    int N;
    fin >> N;
    for(int i=0;i<N;++i)
    {
        fin >> range[i];
    }
    for(int i=0;i<N;++i)
    {
        if(range[0][i]=='1')state[0][i]=1;
        else state[0][i]=0;
    }
    for(int i=1;i<N;++i)
    {
        for(int j=0;j<N;++j)
        {
            if(j==0) state[i][j] = range[i][j]=='1'?1:0;
            else if(range[i][j]=='1')
            {
                state[i][j] = min(state[i-1][j],state[i][j-1]);
                state[i][j] = min(state[i][j],state[i-1][j-1]);
                state[i][j]++;
            }
            else
            {
                state[i][j] = 0;
            }
        }
    }
    for(int i=2;i<=N;++i) res[i] = 0;
    for(int i=0;i<N;++i)
    {
        for(int j=0;j<N;++j)
        {
            //cout << state[i][j] << ' ';
            if(state[i][j]>=2)
            {
                for(int k=2;k<=state[i][j];++k)
                {
                    res[k]++;
                }
            }
        }
        //cout << endl;
    }
    for(int i=2;i<=N;++i)
    {
        if(res[i]>0) fout << i << ' ' << res[i] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}

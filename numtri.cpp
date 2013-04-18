/*
ID: wanggen3
PROG: numtri
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("numtri.in");
ofstream fout("numtri.out");
int R[1001][1001];
int N;
int main(int argv,char*argc[])
{
    fin >> N;
    for(int i=1; i <= N; ++i)
    {
        for(int j=1; j <=i; ++j)
        {
            fin>>R[i][j];
        }
    }
    for(int i=2; i<=N; ++i)
    {
        for(int j=1; j<=i; ++j)
        {
            if(j==1) R[i][j] += R[i-1][j];
            else if(j==i) R[i][j] += R[i-1][j-1];
            else R[i][j] += (R[i-1][j-1]>R[i-1][j]?R[i-1][j-1]:R[i-1][j]);
        }
    }
    int max = 0;
    for(int i=1; i <= N;++i)
    {
        if(R[N][i] > max) max = R[N][i];
    }
    fout << max << endl;
    fin.close();
    fout.close();
    return 0;
}

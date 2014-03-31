/*
ID: wanggen3
PROG: game1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("game1.in");
ofstream fout("game1.out");
int main(int argv,char*argc[])
{
    int value[200];
    int N;
    int f[200][200][2];
    fin >> N;
    for(int i=0;i<N;++i)
    {
        fin >> value[i];
        f[i][i][1] = value[i];
        f[i][i][0] = 0;
    }
    int left,right;
    for(int step =1;step < N;++step)
    {
        for(int i=0; i+step < N;++i)
        {
            left = value[i]+f[i+1][i+step][0];
            right = value[i+step]+f[i][i+step-1][0];
            if(left>right)
            {
                f[i][i+step][1] = left;
                f[i][i+step][0] = f[i+1][i+step][1];
            }
            else
            {
                f[i][i+step][1] = right;
                f[i][i+step][0] = f[i][i+step-1][1];
            }
        }
    }
    fout << f[0][N-1][1] << ' ' << f[0][N-1][0] << '\n';
    fin.close();
    fout.close();
    return 0;
}

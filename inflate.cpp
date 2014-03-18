/*
ID: wanggen3
PROG: inflate
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("inflate.in");
ofstream fout("inflate.out");
int main(int argv,char*argc[])
{
    int M,N;
    int cost[10001], value[10001];
    int maxPoint[10001][2];
    fin >> M >> N;
    for(int i=1; i <= N; ++i)
    {
        fin >> value[i] >> cost[i];
    }
    for(int i=0; i <= M; ++i)
    {
        maxPoint[i][0] = 0;
    }
    int ind,tmpMax,preInd;
    for(int iN=1;iN <= N; ++iN)
    {
        preInd = (iN-1)%2;
        ind = iN % 2;
        for(int iM = 0; iM <= M; ++iM)
        {
            maxPoint[iM][ind] = maxPoint[iM][preInd];
            if(iM>= cost[iN])
            {
                tmpMax = maxPoint[iM-cost[iN]][ind]+value[iN];
                if(tmpMax > maxPoint[iM][ind]) maxPoint[iM][ind] = tmpMax;
            }
        }
    }
    fout << maxPoint[M][N%2] << endl;
    fin.close();
    fout.close();
    return 0;
}

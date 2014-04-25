/*
ID: wanggen3
PROG: job
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("job.in");
ofstream fout("job.out");
int main(int argv,char*argc[])
{
    int N,M1,M2;
    int m1[30],m2[30];
    int cm1[30],cm2[30];
    fin >> N >> M1 >> M2;
    for(int i=0;i<M1;++i){fin>>m1[i];cm1[i]=0;}
    for(int i=0;i<M2;++i){fin>>m2[i];cm2[i]=0;}
    int table[1000];
    for(int i=0;i<N;++i)table[i]=0;
    int minTime,minTime2,index;
    for(int i=0;i<N;++i)
    {
        
        minTime = 99999999;
        for(int j=0;j<M1;++j)
        {
            if(m1[j]+cm1[j]<minTime)
            {
                minTime = m1[j]+cm1[j];
                index = j;
            }
        }
        cm1[index] += m1[index];
        table[i] += cm1[index];
        minTime2 = 99999999;
        for(int j=0;j<M2;++j)
        {
            if(cm2[j]+m2[j]<minTime2)
            {
                minTime2 = cm2[j]+m2[j];
                index = j;
            }
        }
        cm2[index] += m2[index];
        table[N-i-1] += cm2[index];
    }
    minTime = 0;
    minTime2 = 0;
    for(int i=0;i<M1;++i) minTime = max(minTime,cm1[i]);
    for(int i=0;i<N;++i) minTime2 = max(minTime2,table[i]);
    fout << minTime << ' ' << minTime2 << endl;
    fin.close();
    fout.close();
    return 0;
}

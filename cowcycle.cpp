/*
ID: wanggen3
PROG: cowcycle
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
ifstream fin("cowcycle.in");
ofstream fout("cowcycle.out");
int F,R,F1,F2,R1,R2;
int f[20],r[20];
int minF[20],minR[20];
double minDelta;
double getDelta()
{
    vector<double> steps;
    for(int i=0;i<F;++i)
    {
        for(int j=0;j<R;++j)
        {
            steps.push_back(f[i]*1.0/r[j]);
        }
    }
    sort(steps.begin(),steps.end());
    int size = steps.size();
    /*
    for(int i=0;i<size;++i)
    {
        cout << steps[i] << ' ';
    }
    cout << endl;
    */
    if(steps[size-1]/steps[0]<3) return 1e9;
    size--;
    for(int i=0;i<size;++i)
    {
        steps[i] = steps[i+1]-steps[i];
    }
    double mean = 0.0,sq = 0.0;
    for(int i=0;i<size;++i)
    {
        mean += steps[i];
        sq += steps[i]*steps[i];
    }
    mean /= size;
    sq = sq/size - mean*mean;
    return sq;
}
void dfsR(int step,int index);
void dfsF(int step,int index)
{
    if(step==F)
    {
        dfsR(0,R1);
    }
    else
    {
        for(int i=index;i<=F2;++i)
        {
            f[step] = i;
            dfsF(step+1,i+1);
        }
    }
}
void dfsR(int step,int index)
{
    if(step==R)
    {
        if(f[F-1]*r[R-1] < 3*f[0]*r[0]) return;
        double tempDelta = getDelta();
        if(tempDelta < minDelta)
        {
            //cout << tempDelta << endl;
            minDelta = tempDelta;
            for(int i=0;i<F;++i) minF[i] = f[i];
            for(int i=0;i<R;++i) minR[i] = r[i];
        }
    }
    else
    {
        for(int i=index;i<=R2;++i)
        {
            r[step] = i;
            dfsR(step+1,i+1);
        }
    }
}
int main(int argv,char*argc[])
{
    fin >> F >> R;
    fin >> F1 >> F2 >> R1 >> R2;
    minDelta = 1e9;
    dfsF(0,F1);
    for(int i=0;i<F-1;++i) fout << minF[i] <<  ' ';
    fout << minF[F-1] << endl;
    for(int i=0;i<R-1;++i) fout << minR[i] <<  ' ';
    fout << minR[R-1] << endl;
    fin.close();
    fout.close();
    return 0;
}

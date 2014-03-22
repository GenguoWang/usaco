/*
ID: wanggen3
PROG: humble
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;
ifstream fin("humble.in");
ofstream fout("humble.out");
int main(int argv,char*argc[])
{
    unsigned int K, N;
    unsigned int value[100];
    unsigned int index[100];
    unsigned int hum[100001];
    fin >> K >> N;
    for (int i= 0; i < K; ++i)
    {
        fin >> value[i];
        index[i]  = 0;
    }
    int nHum = 0;
    hum[nHum++] = 1;
    int temp,preHum,tempHum;
    while(nHum<=N){
        preHum = hum[nHum-1];
        for(int i = 0; i < K; ++i)
        {
            while(value[i]*hum[index[i]]<=preHum) index[i]++;
            tempHum = value[i]*hum[index[i]];
            if(i==0) temp = tempHum;
            else
            {
                if(tempHum<temp) temp = tempHum;
            }
        }
        hum[nHum++] = temp;
    }
    fout << hum[N] << endl;
    fin.close();
    fout.close();
    return 0;
}

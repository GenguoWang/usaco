/*
ID: wanggen3
PROG: stamps
LANG: C++
*/
#include <iostream>
#include <fstream>
#define MAX 99999999
using namespace std;
ifstream fin("stamps.in");
ofstream fout("stamps.out");
int main(int argv,char*argc[])
{
    int K,N;
    int possible[10001];
    int value[51];
    fin >> K >> N;
    for(int i = 0; i < N; ++i)
    {
        fin >> value[i];
    }
    possible[0]=0;
    int nextValueToTest=1;
    int nextIndex,preIndex;
    int tmpValue;
    while(true)
    {
        nextIndex = nextValueToTest % 10001;
        tmpValue = MAX;
        for(int i=0; i < N; ++i)
        {
            if(nextValueToTest-value[i] >= 0)
            {
                preIndex = (nextValueToTest-value[i])%10001;
                if(possible[preIndex]+1 < tmpValue) tmpValue = possible[preIndex]+1;
            }
        }
        if(tmpValue>K) break;
        possible[nextIndex] = tmpValue;
        nextValueToTest++;
    }
    fout << nextValueToTest-1 << endl;
    fin.close();
    fout.close();
    return 0;
}

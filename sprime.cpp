/*
ID: wanggen3
PROG: sprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
ifstream fin("sprime.in");
ofstream fout("sprime.out");
int N;
bool isPrime(int num)
{
    int max = sqrt((double)num);
    for(int i=2; i <= max; ++i)
    {
        if(num%i==0) return false;
    }
    return true;
}
int main(int argv,char*argc[])
{
    vector<int> res[9];
    fin >> N;
    res[1].push_back(2);
    res[1].push_back(3);
    res[1].push_back(5);
    res[1].push_back(7);
    int temp;
    for(int i=2; i <= N; ++i)
    {
        for(int j=0; j < res[i-1].size(); ++j)
        {
            for(int k=1; k <= 9; ++k)
            {
                temp = res[i-1][j]*10+k;
                if(isPrime(temp))
                {
                    res[i].push_back(temp);
                }
            }
        }
    }
    for(int i=0; i < res[N].size();++i)
    {
        fout << res[N][i] << endl;
    }
    fin.close();
    fout.close();
    return 0;
}

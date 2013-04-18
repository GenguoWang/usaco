/*
ID: wanggen3
PROG: pprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
ifstream fin("pprime.in");
ofstream fout("pprime.out");
int w[4];
int a,b;
bool f11;
bool isPrime(int num)
{
    int max = sqrt(num);
    for(int i=2; i <= max; ++i)
    {
        if(num % i == 0) return false;
    }
    return true;
}
void work(int now)
{
    int res;
    if(now == 0)
    {
        res = 0;
        res += w[0]*1000000;
        res +=w[1] * 100000;
        res += w[2]*  10000;
        res += w[3] *  1000;
        res += w[2] *   100;
        res += w[1] *    10;
        res += w[0] * 1;
        if(res==0) return;
        while(res%10==0) res /= 10;
        if(a<=res && res <= b && isPrime(res))
        {
            if(res > 11 && f11&&11>=a && 11<=b)
            {
                fout << 11 << endl;
                f11 = false;
            }
            fout << res << endl;    
        } 
    }
    else
    {
        for(int i=0; i <=9; ++i)
        {
            w[4-now] = i;
            work(now-1);
        }
    }
}
int main(int argv,char*argc[])
{
    fin >> a >> b;
    f11 = true;
    work(4);
    fin.close();
    fout.close();
    return 0;
}

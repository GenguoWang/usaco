/*
ID: wanggen3
PROG: ariprog
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
#define fcin fin
#define fcout fout
int main(int argc,char *argv[])
{
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");
    int N,M;
    fcin >> N >> M;
    vector<int> number(M*M*2+1);
    vector<int> arr;
    for(int i=0; i <=M;++i)
    {
        for(int j=i;j<=M;++j)
        {
            number[i*i+j*j] = 1;
        }
    }
    for(int i=0; i < M*M*2+1; ++i)
    {
        if(number[i]) arr.push_back(i);
    }
    int max=M*M*2;
    int a;
    bool ok;
    int count = 0;
    for(int n=1; n <= max; ++n)
    {
        for(int i=0; i < arr.size();++i)
        {
            a = arr[i];
            if(a+n*(N-1)>max)break;
            ok = true;
            for(int j=0; j <= N-1; ++j)
            {
                if(!number[a+n*j])
                {
                    ok = false;
                    break;
                }
            }
            if(ok)
            {
                 fcout << a << " " << n << endl;
                 count++;
            }
        }
    }
    if(count==0) fcout << "NONE" << endl
    return 0;
}

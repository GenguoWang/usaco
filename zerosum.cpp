/*
ID: wanggen3
PROG: zerosum
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("zerosum.in");
ofstream fout("zerosum.out");
int main(int argv,char*argc[])
{
    int n,i;
    int op[10];
    fin >> n;
    for(i=0; i <=n; ++i) op[i] = 0;
    op[n] = 2;
    i=1;
    int res,p,tmp;
    while(i>=1)
    {
        op[i]++;
        if(op[i]>3)
        {
            op[i] = 0;
            i--;
        }
        else if(i<n-1)
        {
            i++;
        }
        else
        {
            res = 0;
            p = 2;
            tmp = 0;
            for(int j=1;j<=n;++j)
            {
                tmp = tmp*10+j;
                if(op[j]!=1)
                {
                    if(p==2)
                    {
                        res += tmp;
                    }
                    else
                    {
                        res -= tmp;
                    }
                    p = op[j];
                    tmp = 0;
                }
            }
            if(res==0)
            {
                for(int j=1;j<=n;++j)
                {
                    fout << j;
                    if(j<n)
                    {
                        if(op[j]==1) fout << ' ';
                        else if(op[j]==2) fout << '+';
                        else if(op[j]==3) fout << '-';
                    }
                }
                fout << endl;
            }
        }
    }
    fin.close();
    fout.close();
    return 0;
}

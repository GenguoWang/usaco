/*
ID: wanggen3
PROG: nuggets
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
ifstream fin("nuggets.in");
ofstream fout("nuggets.out");
int main(int argv,char*argc[])
{
    int N;
    int pack[10];
    int minNum = 9000;
    fin >> N;
    for(int i=0;i<N;++i)
    {
        fin >> pack[i];
        if(pack[i]<minNum) minNum = pack[i];
    }
    if(minNum==1)
    {
        fout << 0 << endl;
    }
    else
    {
        vector<unsigned int> num(minNum+1);
        int left = minNum;
        int temp;
        int pos;
        for(int k=1;k<minNum;++k)
        {
            for(int i=0;i<N;++i)
            {
                for(int j=0;j<=minNum;++j)
                {
                    temp = pack[i]+num[j];
                    pos = temp%minNum;
                    if(num[pos]==0||num[pos] > temp)
                    {
                        num[pos] = temp;
                    }
                }
            }
        }
        bool isOK = true;
        int maxNum = 0;
        for(int i=0;i<minNum;++i)
        {
            if(num[i]==0)
            {
                isOK = false;
                break;
            }
            else
            {
                if(num[i]>maxNum)maxNum = num[i];
            }
        }
        if(isOK) fout << maxNum-minNum << endl;
        else fout << 0 << endl;
    }
    fin.close();
    fout.close();
    return 0;
}

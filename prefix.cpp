/*
ID: wanggen3
PROG: prefix
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;
ifstream fin("prefix.in");
ofstream fout("prefix.out");
int main(int argv,char*argc[])
{
    int abl[200002];
    memset((void*)abl,0,200002*sizeof(int));
    string str;
    vector<string> pre;
    fin >> str;
    int n=0;
    while(str != ".")
    {
        n++;
        pre.push_back(str);
        fin >> str;
    }
    string t;
    fin >> str;
    while(fin >> t) str += t;
    abl[0] = 1;
    int size=str.size();
    int best=0;
    for(int i=0;i<=size;++i)
    {
        if(abl[i])
        {
           if(i>best) best = i;
           for(int j=0;j<n;++j)
           {
                if(i+pre[j].size()<=size&&str.compare(i,pre[j].size(),pre[j])==0)
                {
                    abl[i+pre[j].size()] = 1;
                }
           }
        }
    }
    fout << best << endl;
    fin.close();
    fout.close();
    return 0;
}

/*
ID: wanggen3
PROG: ratios
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("ratios.in");
ofstream fout("ratios.out");
int main(int argv,char*argc[])
{
    int v[3][3],res[3],r[3];
    for(int i = 0; i < 3; ++i) fin >> res[i];
    for(int j=0;j<3;++j)
    {
        for(int i = 0; i < 3; ++i) fin >> v[j][i];
    }
    bool flag;
    int ratio;
    for(r[0]=0;r[0]<=100;++r[0])
    {
        for(r[1]=0;r[1]<=100;++r[1])
        {
            for(r[2]=0;r[2]<=100;++r[2])
            {
                flag = true;
                ratio = 0;
                for(int i=0;i<3;++i)
                {
                    int temp=0;
                    for(int j=0;j<3;++j)
                    {
                        temp += r[j]*v[j][i];
                    }
                    if(res[i]==0 && temp!=0)flag=false;
                    else if(temp==0 && res[i]!=0) flag = false;
                    else if(temp==0 && res[i] == 0)
                    {
                        
                    }
                    else if(temp%res[i]!=0)flag=false;
                    else
                    {
                        if(ratio==0) ratio = temp/res[i];
                        else if(temp/res[i] != ratio) flag = false;
                    }
                }
                if(flag)
                {
                    for(int j=0;j<3;++j)
                    {
                        fout << r[j] << " " ;
                    }
                    fout << ratio << endl;
                    goto end;
                }
            }
        }
    }
    end:
    if(!flag)
    {
        fout << "NONE" << endl;
    }
    fin.close();
    fout.close();
    return 0;
}

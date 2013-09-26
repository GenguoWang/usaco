/*
ID: wanggen3
PROG: ttwo
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("ttwo.in");
ofstream fout("ttwo.out");
int main(int argv,char*argc[])
{
    char m[12][12];
    int cx,cy,fx,fy;
    int ci,cj,fi,fj;
    for(int i=0;i<12;++i)
    {
        m[i][0] = '*';
        m[i][11] = '*';
        m[0][i] = '*';
        m[11][i] = '*';
    }
    for(int i=1;i<=10;++i)
    {
        for(int j=1;j<=10;++j)
        {
            fin >> m[i][j];
            if(m[i][j]=='F')
            {
                fi = i;
                fj = j;
            }
            else if(m[i][j]=='C')
            {
                ci = i;
                cj = j;
            }
        }
    }
    int i = 1;
    cx = -1;cy = 0;fx=-1;fy=0;
    int tmp;
    /*
    -1 0  cy = cx*(-1),cx=cy;
    0 1
    1 0
    0 -1
    */
    bool found = false;
    while(i < 500*500)
    {
        if(m[ci+cx][cj+cy]=='*')
        {
            tmp = cy;
            cy = cx*(-1);
            cx = tmp;
        }
        else
        {
            ci += cx;
            cj += cy;
        }
        if(m[fi+fx][fj+fy]=='*')
        {
            tmp = fy;
            fy = fx*(-1);
            fx = tmp;
        }
        else
        {
            fi += fx;
            fj += fy;
        }
        if(ci==fi&&cj==fj)
        {
            fout << i << endl;
            found = true;
            break;
        }
        i++;
    }
    if(!found) fout << 0 << endl;
    fin.close();
    fout.close();
    return 0;
}

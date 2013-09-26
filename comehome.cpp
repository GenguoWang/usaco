/*
ID: wanggen3
PROG: comehome
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("comehome.in");
ofstream fout("comehome.out");
int index(char c)
{
    if(c>='a' && c<='z') return 26+(int)c-(int)'a';
    if(c>='A' && c<='Z') return (int)c-(int)'A';
}
int main(int argv,char*argc[])
{
    int map[52][52];
    for(int i=0;i<52;++i)
    {
        for(int j=0;j<52;++j)
        {
            map[i][j] = 99999999;
        }
    }
    int n;
    fin >> n;
    char a,b;
    int d,ia,ib;
    while(n--)
    {
        fin >> a >> b >> d;
        ia = index(a);
        ib = index(b);
        if(d<map[ia][ib])
        {
            map[ia][ib] = d;
            map[ib][ia] = d;
        }
    }
    for(int k=0;k<52;++k)
    {
        for(int i=0;i<52;++i)
        {
            for(int j=0;j<52;++j)
            {
                if(map[i][k]+map[k][j]<map[i][j]) map[i][j] = map[i][k]+map[k][j];
            }
        }
    }
    int min=99999999;
    d=-1;
    ia = index('Z');
    for(int i='A';i<'Z';++i)
    {
        if(map[index(i)][ia] < min)
        {
            min = map[index(i)][ia];
            d = i;
        }
    }
    fout << (char)d << ' ' << min << endl;
    fin.close();
    fout.close();
    return 0;
}

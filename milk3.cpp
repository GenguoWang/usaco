/*
ID: wanggen3
PROG: milk3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
using namespace std;
int s[21][21][21];
set<int> ans;
int A,B,C;
void tran(int&a,int&b,int A,int B)
{
    int m = a;
    if(m>B-b) m = B-b;
    a = a-m;
    b = b+m;
}
void work(int a,int b,int c)
{
    if(s[a][b][c]) return;
    s[a][b][c] = 1;
    if(a==0) ans.insert(c);
    int s1,s2;
    s1 = a;s2=b;
    tran(s1,s2,A,B);
    work(s1,s2,c);
    s1 = a;s2=b;
    tran(s2,s1,B,A);
    work(s1,s2,c);
    s1 = b;s2=c;
    tran(s1,s2,B,C);
    work(a,s1,s2);
    s1 = b;s2=c;
    tran(s2,s1,C,B);
    work(a,s1,s2);
    s1 = a;s2=c;
    tran(s1,s2,A,C);
    work(s1,b,s2);
    s1 = a;s2=c;
    tran(s2,s1,C,A);
    work(s1,b,s2);
}
int main(int argv,char*argc[])
{
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");
    fin >> A >> B >> C;
    memset((void*)s,0,sizeof(s));
    work(0,0,C);
    bool first = true;
    for(set<int>::iterator it=ans.begin();it !=ans.end();++it)
    {
        if(first) fout << *it;
        else fout <<" " << *it;
        first = false;
    }
    fout << endl;
    //s[0][0][c] = 1;
    //ans.insert(c);
    fin.close();
    fout.close();
    return 0;
}

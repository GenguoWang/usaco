/*
ID: wanggen3
PROG: fracdec
LANG: C++
*/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#define LN 76
using namespace std;
ifstream fin("fracdec.in");
ofstream fout("fracdec.out");
int gcd(int a,int b)
{
    if(a>b)
    {
        if(b==0) return a;
        return gcd(a%b,b);
    }
    else
    {
        if(a==0) return b;
        return gcd(b%a,a);
    }
}
int main(int argv,char*argc[])
{
    int N,D;
    fin >> N >> D;
    if(N%D==0)
    {
        fout << N/D << ".0" << endl;
        return 0;
    }
    //保证分子分母互质
    int g = gcd(N,D);
    N /= g;
    D /= g;
    //取出分母中2和5的成分，这两者不产生循环小数,影响循环前的数字
    int cnt=0;
    while(D%10==0){cnt++;D/=10;}
    while(D%2==0){cnt++;D/=2;N*=5;}
    while(D%5==0){cnt++;D/=5;N*=2;}
    //计算循环部位有多少位，也就是多少个999...99可以整除分母
    int p9=1,s9=9%D,c9=9%D;
    while(s9 != 0)
    {
        c9 = c9*10%D;
        s9 += c9;
        s9 %= D;
        p9++;
    }
    //计算整数部分和小数部分
    int p1=N/D, p0=N%D;
    char buffer[33];
    sprintf(buffer,"%d",p1);
    string str = string(buffer);
    //根据2和5的成分确定小数点位置
    int pc = 0,off=str.size()-cnt;
    if(off <=0)
    {
        fout << "0.";
        pc=2;
        for(int i=0; i+off<0;++i)
        {
            if(pc%LN==0&&pc>0) fout << "\n";
            fout << "0";
            pc++;
        }
    }
    for(int i=1;i<=str.size();++i)
    {
        if(pc%LN==0&&pc>0) fout << "\n";
        fout << str[i-1];
        pc++;
        if(pc==off) {fout << ".";pc++;}
    }
    //输出循环部分
    if(D>1)
    {
        if(pc%LN==0&&pc>0) fout << "\n";
        fout << "(";
        pc++;
        if(pc%LN==0&&pc>0) fout << "\n";
        for(int i=0; i < p9;++i)
        {
            if(pc%LN==0&&pc>0) fout << "\n";
            pc++;
            p0 *=10;
            fout << p0/D;
            p0 %=D;
        }
        if(pc%LN==0&&pc>0) fout << "\n";
        fout << ")";
        pc++;
    }
    fout << endl;
    fin.close();
    fout.close();
    return 0;
}

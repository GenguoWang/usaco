/*
ID: wanggen3
PROG: fact4
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("fact4.in");
ofstream fout("fact4.out");
int main(int argv,char*argc[])
{
    int N;
    fin >> N;
    int temp = N;
    int countFive=0;
    while(temp/5>0)
    {
        countFive += temp/5;
        temp /= 5;
    }
    int lastNum=1;
    for(int i=2; i <= N; ++i)
    {
        temp = i;
        while(countFive>0 && temp %2==0)
        {
            countFive--;
            temp /= 2;
        }
        while(temp%5==0) temp /= 5;
        lastNum = (lastNum*temp)%10;
    }
    fout << lastNum << endl;
    fin.close();
    fout.close();
    return 0;
}

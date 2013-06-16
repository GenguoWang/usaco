/*
ID: wanggen3
PROG: subset
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;
ifstream fin("subset.in");
ofstream fout("subset.out");
long long v[40][1000];
bool flag[40][1000];
long long f(int num,int p)
{
	if(p<0) p=-p;
	if(p>num*(num+1)/2) return 0;
	if(flag[num][p]) return v[num][p];
	if(num==1 && p==1) return 1;
	v[num][p] = f(num-1,num-p)+f(num-1,num+p);
	flag[num][p] = true;
	return v[num][p];
}
int main(int argv,char*argc[])
{
	int N;
	fin >> N;
	memset((void*)flag,0,sizeof(flag));
	fout << f(N,0)/2 << endl;
    fin.close();
    fout.close();
    return 0;
}
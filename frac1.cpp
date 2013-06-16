/*
ID: wanggen3
PROG: frac1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <set>
#include <utility>
using namespace std;
ifstream fin("frac1.in");
ofstream fout("frac1.out");
class myless
{
public:
	bool operator () (pair<int,int> a,pair<int,int> b)
	{
		return double(a.first)/a.second < double(b.first)/b.second;
	}
};
int gcd(int a,int b)
{
	int big=a,small=b;
	if(a<b)
	{
		big=b;
		small=a;
	}
	if(small == 0) return big;
	else return gcd(small,big%small);
}
int main(int argv,char*argc[])
{
    set<pair<int,int>,myless> res;
	int N;
	fin >> N;
	int d;
	for(int i=1; i <=N-1;++i)
	{
		for(int j=i+1; j<=N;++j)
		{
			d = gcd(i,j);
			res.insert(pair<int,int>(i/d,j/d));
		}
	}
	fout << "0/1" << endl;
	for(set<pair<int,int>,myless>::iterator it=res.begin(); it != res.end();++it)
	{
		fout << it->first << "/" << it->second << endl;
	}
	fout << "1/1" << endl;
    fin.close();
    fout.close();
    return 0;
}
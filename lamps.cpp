/*
ID: wanggen3
PROG: lamps
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <set>
#include <utility>
#include <algorithm>
#include <string>
using namespace std;
ifstream fin("lamps.in");
ofstream fout("lamps.out");
set<unsigned int> res;
void work(int c,unsigned int now)
{
	if(c==0)
	{
		res.insert(now);
	}
	else
	{
		work(c-1,now ^ (1<<6)-1);
		work(c-1,now^(0x2a));
		work(c-1,now^(0x15));
		work(c-1,now^0x24);
	}
}
int main(int argv,char*argc[])
{
	int N;
	int C;
	int temp;
	fin >> N >> C;
	fin>>temp;
	bool flag = false;
	int a[6] = {-1,-1,-1,-1,-1,-1};
	while(temp!=-1)
	{
		a[(temp-1)%6] = 1;
		fin >> temp;
	}
	fin>>temp;
	while(temp!=-1)
	{
		if(a[(temp-1)%6]==1)
		{
			flag = true;
			break;
		}
		a[(temp-1)%6] = 0;
		fin >> temp;
	}
	if(flag)
	{
		fout<<"IMPOSSIBLE" << endl;
	}
	if(C>4) C = (C+1)%2+3;
	work(C,(1<<6)-1);
	int cnt=0;
	for(set<unsigned int>::iterator it=res.begin();it != res.end();++it)
	{
		flag = false;
		for(int i=0; i < 6;++i)
		{
			if(a[i]!=-1 && a[i] != (((*it)>>(5-i%6))&0x1))
			{
				flag = true;
				break;
			}
		}
		if(flag) continue;
		cnt++;
		for(int i=0; i < N; ++i)
		{
			fout << (((*it)>>(5-i%6))&0x1);
		}
		fout << endl;
	}
	if(cnt==0)
	{
		fout<<"IMPOSSIBLE" << endl;
	}
    fin.close();
    fout.close();
    return 0;
}
/*
ID: wanggen3
PROG: holstein
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
ifstream fin("holstein.in");
ofstream fout("holstein.out");
int V,G;
int req[26];
int pov[16][26];
int path[26];
bool dfs(int s,int dep)
{
	if(dep==0)
	{
		for(int j=1; j<=V;++j) if(req[j]>0) return false;
		return true;
	}
	for(int i=s; i<=G; ++i)
	{
		path[dep] = i;
		for(int j=1; j<=V;++j) req[j] -= pov[i][j];
		if(dfs(i+1,dep-1)) return true;
		for(int j=1; j<=V;++j) req[j] += pov[i][j];
	}
	return false;
}
int main(int argv,char*argc[])
{
	fin >> V;
	for(int i=1; i<=V;++i)
	{
		fin>>req[i];
	}
	fin >> G;
	for(int i=1; i<=G;++i)
	{
		for(int j=1; j<=V;++j)
		{
			fin>>pov[i][j];
		}
	}
	int dep;
	for(dep=1; dep<=G;++dep)
	{
		if(dfs(1,dep)) break;
	}
	fout << dep;
	for(int i=dep; i>=1; --i)
	{
		fout << " " << path[i];
	}
	fout << endl;
    fin.close();
    fout.close();
    return 0;
}
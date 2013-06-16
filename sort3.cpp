/*
ID: wanggen3
PROG: sort3
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
ifstream fin("sort3.in");
ofstream fout("sort3.out");

int main(int argv,char*argc[])
{
    int N;
	fin >> N;
	vector<int> ori(N),sot(N);
	int cnt[4][4];
	memset((void*)cnt,0,sizeof(cnt));
	int temp;
	for(int i=0; i<N;++i)
	{
		fin >> temp;
		ori[i] = temp;
		sot[i] = temp;
	}
	sort(sot.begin(),sot.end());
	for(int i=0; i < N;++i)
	{
		cnt[ori[i]][sot[i]]++;
	}
	int max = 0;
	for(int i=1; i <= 2; ++i)
	{
		for(int j=i+1;j<=3;++j)
		{
			if(cnt[i][j]>cnt[j][i])
			{
				max+=cnt[j][i];
				cnt[i][j] -= cnt[j][i];
				cnt[j][i] = 0;
			}
			else
			{
				max+=cnt[i][j];
				cnt[j][i] -= cnt[i][j];
				cnt[i][j] = 0;
			}
		}
	}
	if(cnt[1][2])
	{
		max += 2*cnt[1][2];
	}
	else
	{
		max += 2*cnt[2][1];
	}
	fout << max << endl;
    fin.close();
    fout.close();
    return 0;
}
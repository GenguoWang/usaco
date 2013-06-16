/*
ID: wanggen3
PROG: preface
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
ifstream fin("preface.in");
ofstream fout("preface.out");
int main(int argv,char*argc[])
{
	int N;
	fin >> N;
	int a[7];
	memset((void*)a,0,sizeof(a));
	int num,temp;
	for(int j=1; j<=N;++j)
	{
		temp = j;
		for(int i=0; i < 7; i += 2)
		{
			num = temp%10;
			temp /= 10;
			switch(num)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				a[i] += num;
				break;
			case 4:
				a[i]++;
				a[i+1]++;
				break;
			case 5:
			case 6:
			case 7:
			case 8:
				a[i] += (num-5);
				a[i+1]++;
				break;
			case 9:
				a[i]++;
				a[i+2]++;
				break;
			}
		}
	}
	char c[7] = {'I','V','X','L','C','D','M'};
	for(int i=0;i<7;i++)
	{
		if(a[i]==0) break;
		fout << c[i] << " " << a[i] << endl;
	}
    fin.close();
    fout.close();
    return 0;
}

/*
ID: wanggen3
PROG: runround
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
ifstream fin("runround.in");
ofstream fout("runround.out");
int main(int argv,char*argc[])
{
	int N;
	fin >> N;
	int f[10];
	int p,size;
	bool flag;
	int str[12];
	int temp;
	for(unsigned int i=N+1;;++i)
	{
		//itoa(i,str,10);
		temp = i;
		size = 0;
		while(temp>0)
		{
			str[size++] = temp%10;
			temp /=10;
		}
		p = size-1;
		//size = strlen(str);
		memset((void*)f,0,sizeof(f));
		flag = true;
		for(int j=0;j<size;++j)
		{
			p = (p+size-str[p]%size)%size;
			if(f[str[p]])
			{
				flag = false;
				break;
			}
			f[str[p]] = 1;
		}
		if(flag)
		{
			fout << i << endl;
			break;
		}
	}
    fin.close();
    fout.close();
    return 0;
}

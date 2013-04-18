/*
ID: wanggen3
PROG: clocks
LANG: C++
*/
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#define fcin fin
#define fcout fout
ifstream fin("clocks.in");
ofstream fout("clocks.out");
void turn(int * clock,int i)
{
	switch(i)
	{
	case 1:	//ABDE
		clock[0] = clock[0]+3;
		clock[1] = clock[1]+3;
		clock[3] = clock[3]+3;
		clock[4] = clock[4]+3;
		break;
	case 2://ABC
		clock[0] += 3;
		clock[1] += 3;
		clock[2] += 3;
		break;
	case 3://BCEF
		clock[1] += 3;
		clock[2] += 3;
		clock[4] += 3;
		clock[5] += 3;
		break;
	case 4://ADG
		clock[0] += 3;
		clock[3] += 3;
		clock[6] += 3;
		break;
	case 5://BDEFH
		clock[1] += 3;
		clock[3] += 3;
		clock[4] += 3;
		clock[5] += 3;
		clock[7] += 3;
		break;
	case 6://CFI
		clock[2] += 3;
		clock[5] += 3;
		clock[8] += 3;
		break;
	case 7://DEGH
		clock[3] += 3;
		clock[4] += 3;
		clock[6] += 3;
		clock[7] += 3;
		break;
	case 8://GHI
		clock[6] += 3;
		clock[7] += 3;
		clock[8] += 3;
		break;
	case 9://EFHI 
		clock[4] += 3;
		clock[5] += 3;
		clock[7] += 3;
		clock[8] += 3;
		break;
	}
	for(int i=0; i < 9;++i) clock[i] %= 12;
}
bool check(int * clock)
{
	for(int i=0; i < 9; ++i) if(clock[i] != 0) return false;
	return true;
}
int minstep;
int path[10];
int finalPath[10];
void work(int *clock,int now,int step)
{
	if(check(clock))
	{
		if(step < minstep) minstep = step;
		memcpy((void*)finalPath,(void*)path,sizeof(finalPath));
		return;
	}
	if(now > 9) return;
	int temp[9];
	for(int i=3; i>=0; --i)
	{
		memcpy((void*)temp,(void*)clock,sizeof(temp));
		for(int j=0; j < i; ++j)
		{
			turn(temp,now);
		}
		path[now] = i;
		work(temp,now+1,step+i);
	}
}
int main(int argc, char* argv[])
{
	int clock[9];
	for(int i=0; i < 9; ++i) fcin >> clock[i];
	//turn(clock,5);
	//turn(clock,8);
	//turn(clock,4);
	//turn(clock,9);
	//for(int i=0; i < 9; ++i) fcout << clock[i];
	minstep = 999999;
	memset((void *)path,0,sizeof(path));
	memset((void *)finalPath,0,sizeof(finalPath));
	work(clock,1,0);
	//fcout << minstep << endl;
	bool first = true;
	for(int i = 1; i <=9; ++i)
	{
		for(int j=0; j < finalPath[i]; ++j)
		{
			if(first) fcout << i;
			else fcout << " " << i;
			first = false;
		}
	}
	fcout << endl;
	return 0;
}


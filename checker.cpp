/*
ID: wanggen3
PROG: checker
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
ifstream fin("checker.in");
ofstream fout("checker.out");
int N;
unsigned int s[14][14];
int path[14];
int cnt=0;
unsigned int bitmap[14];
bool check()
{
    int temp = 0;
    for(int i=1; i<=N;++i)
    {
        temp = 0;
        for(int j=1; j<=N;++j)
        {
            temp+=s[j][i];
        }
        if(temp > 1) return false;
    }
    int temp1,temp2;
    for(int i=1; i<=N;++i)
    {
        temp1 = 0;
        temp2 = 0;
        for(int j=0; j<N;++j)
        {
            if(i+j>N) break;
            temp1+=s[1+j][i+j];
            temp2+=s[i+j][1+j];
        }
        if(temp1 > 1) return false;
        if(temp2 > 1) return false;
    } 
    for(int i=1; i<=N;++i)
    {
        temp1 = 0;
        temp2 = 0;
        for(int j=0; j<N;++j)
        {
            if(i-j<1) break;
            temp1+=s[1+j][i-j];
            temp2+=s[N+1-i+j][N-j];
        }
        if(temp1 > 1) return false;
        if(temp2 > 1) return false;
    } 
    return true;
}
void bitwork(int num)
{
	if(num>N)
	{
		cnt++;
		if(cnt <=3)
		{
			fout <<path[1];
			for(int i=2; i<= N; ++i)
			{
				fout << " " << path[i];
			}
			fout << endl;
		}
	}
	else
	{
		unsigned int bittemp[14];
		memcpy((void*)bittemp,(void*)bitmap,sizeof(bittemp));
		unsigned int now = bittemp[num];
		int i=0;
		while(now>0)
		{
			if(now&0x1)
			{
				for(int j=num+1;j<=N;++j)
				{
					bitmap[j] = bitmap[j]&(~(1<<i));
					if(i+j-num <N) bitmap[j] = bitmap[j]&(~(1<<(i+j-num)));
					if(i-j+num>=0)  bitmap[j] = bitmap[j]&(~(1<<(i-j+num)));
				}
				path[num] = i+1;
				bitwork(num+1);
				memcpy((void*)bitmap,(void*)bittemp,sizeof(bittemp));
			}
			i++;
			now >>=1;
		}
	}
}
void work(int num)
{
    if(num>N)
    {
        cnt++;
		/*
        for(int i=1; i <= N; ++i)
        {
            cout << path[i] << " ";
        }
        cout << endl;
		*/
    }
    else
    {
        for(int i=1; i <= N;++i)
        {
            s[num][i] = 1;
            if(check())
            {
                path[num] = i;
                work(num+1);
            }
            s[num][i] = 0;
        }
    }
}
int main(int argv,char*argc[])
{
    fin >> N;
	/*
    memset((void*)s,0,sizeof(s));
	int c1 = 0;
	if(N>=2)
	{
		for(int i=1; i<=N/2;++i)
		{
			cnt = 0;
			s[1][i] = 1;
			work(2);
			s[1][i] = 0;
			c1 += cnt;
		}
		c1 *= 2;
		if(N%2==1)
		{
			cnt=0;
			s[1][N/2+2] = 1;
			work(2);
			s[1][N/2+2] = 1;
			c1+=cnt;
		}
	}
    cout << c1 << endl;
	*/
	for(int i=1; i <= N;++i) bitmap[i] = (1<<N)-1;
	bitwork(1);
	fout << cnt << endl;
    //memset((void*)s,0,sizeof(s));
	//cnt = 0;
	//work(1);
	//cout << cnt << endl;
    fin.close();
    fout.close();
    return 0;

}


/*
ID: wanggen3
PROG: msquare
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
ifstream fin("msquare.in");
ofstream fout("msquare.out");
int pre[50000];
char op[50000];
int arrayToIndex(int a[],int size)
{
    int f=1;
    int index = 0;
    for(int i=1; i<=size-1;++i) f *= i;
    for(int i=0; i < size;++i)
    {
        int b=0;
        for(int j=0; j < i;++j)
        {
            if(a[j]<a[i]) b++;
        }
        index += f*(a[i]-b-1);
        if(size-i-1!=0)f /= (size-i-1);
    }
    return index+1;
}
class msquare
{
    public:
    int a[8];
    msquare toTrans(int type)
    {
        msquare newS;
        if(type==0)
        {
            for(int i=0;i<8;++i)
            {
                newS.a[i] = a[7-i];
            }
        }
        if(type==1)
        {
            newS.a[0] = a[3];
            newS.a[7] = a[4];
            for(int i=0;i<3;++i)
            {
                newS.a[i+1] = a[i];
                newS.a[7-i-1] = a[7-i];
            }
        }
        if(type==2)
        {
            newS.a[0] = a[0];
            newS.a[1] = a[6];
            newS.a[2] = a[1];
            newS.a[3] = a[3];
            newS.a[4] = a[4];
            newS.a[5] = a[2];
            newS.a[6] = a[5];
            newS.a[7] = a[7];
        }
        return newS;
    }
    int toIndex()
    {
        return arrayToIndex(a,8);
    }
    void output()
    {
        cout << a[0] << a[1]<< a[2]<< a[3]<< endl;
        cout << a[7] << a[6]<< a[5]<< a[4]<< endl;
    }
};
int main(int argv,char*argc[])
{
    msquare source,dest;
    for(int i=0;i<8;++i)source.a[i]=i+1;
    for(int i=0;i<8;++i)fin >> dest.a[i];
    int destIndex = dest.toIndex();
    queue<msquare> q;
    q.push(source);
    pre[source.toIndex()] = -1;
    msquare now;
    while(!q.empty())
    {
        now = q.front();
        if(now.toIndex()==destIndex)
        {
            break;
        }
        q.pop();
        for(int i=0;i<3;++i)
        {
            msquare sa = now.toTrans(i);
            if(pre[sa.toIndex()]==0)
            {
                pre[sa.toIndex()] = now.toIndex();
                op[sa.toIndex()] = (char)((int)'A'+i);
                q.push(sa);
            }
        }
    }
    int cnt=0;
    int nowIndex = now.toIndex();
    int preIndex=-1;
    int tempInt;
    while(pre[nowIndex]!=-1)
    {
        cnt++;
        tempInt = nowIndex;
        nowIndex = pre[nowIndex];
        pre[tempInt] = preIndex;
        preIndex = tempInt;
    }
    fout << cnt << endl;
    int outputCnt=0;
    while(preIndex!=-1)
    {
        if(outputCnt>0 && outputCnt%60==0) fout << endl;
        fout << op[preIndex];
        preIndex = pre[preIndex];
        outputCnt++;
    }
    fout << endl;
    fin.close();
    fout.close();
    return 0;
}

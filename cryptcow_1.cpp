/*
ID: wanggen3
PROG: cryptcow
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
ifstream fin("cryptcow.in");
ofstream fout("cryptcow.out");
#define MOD 99997
int num;
string str;
string objstr = "Begin the Escape execution at the Break of Dawn";
int stepCount;
bool visited[MOD];
vector<string> vis[MOD];
bool isVisited(string &str)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    for(int i=0;i < str.size();++i)
    {
        hash = (hash<<4) + str[i];
        if((x=hash & 0xF0000000)!=0)
        {
            hash ^= (x>>24);
            hash &= ~x;
        }
    }
    hash = hash&0x7FFFFFFF;
    hash %= MOD;
    if(visited[hash])
    {
        for(int i=0;i<vis[hash].size();++i)
        {
            if(str==vis[hash][i])return true;
        }
        vis[hash].push_back(str);
        return false;   
    }
    else
    {
        visited[hash] = true;
        vis[hash].push_back(str);
        return false;
    }
}
bool isMatche(string &str,int i,int len,int j)
{
    while(len--)
    {
        if(str[i++] != objstr[j++]) return false;
    }
    return true;
}
bool dfs(string str)
{
    stepCount++;
    if(stepCount%100000==0) 
        cout << stepCount << endl;
    int c[20],o[20],w[20],a[60];
    int nc=0,no=0,nw=0,na=0;
    int pos=0;
    int strsize = str.size();
    for(int i=0;i<strsize;++i)
    {
        if(str[i]=='C')
        {
            c[nc++] = i;
            a[na++] = i;
        }
        else if(str[i]=='O')
        {
            o[no++] = i;
            a[na++] = i;
        }
        else if(str[i]=='W')
        {
            w[nw++] = i;
            a[na++] = i;
        }
    }
    if(nc==0)
    {
        if(str == objstr)
            return true;   
        else return false;
    }
    if(!isMatche(str,0,c[0],0)) return false;
    if(!isMatche(str,w[nw-1]+1,strsize-w[nw-1]-1,objstr.size()-strsize+w[nw-1]+1)) return false;
    for(int i=0; i < na-1;++i)
    {
            if(a[i+1]-a[i]>1 && objstr.find(str.substr(a[i]+1,a[i+1]-a[i]-1))==string::npos) 
            {
                return false;    
            }
    }
    //if(isVisited(str)) return false;
    for(int i=nc-1;i>=0;--i)
    {
        for(int j=no-1;j>=0;--j)
        {
            for(int k=nw-1;k>=0;--k)
            {
                if(c[i]<o[j]&&o[j]<w[k])
                {
                    if(dfs(str.substr(0,c[i])+str.substr(o[j]+1,w[k]-o[j]-1)
                        +str.substr(c[i]+1,o[j]-c[i]-1)+str.substr(w[k]+1)))
                    return true;
                }
            }
        }
    }
    return false;
}
bool init()
{
    int nc=0,no=0,nw=0;
    int pos=0;
    while((pos=str.find('C',pos))!=string::npos)nc++, pos++;
    if(nc==0) return true;
    pos = 0;
    while((pos=str.find('O',pos))!=string::npos)no++,pos++;
    pos = 0;
    while((pos=str.find('W',pos))!=string::npos)nw++,pos++;
    if(nc!=no && nc!=nw) return false;
    num = nc;
    cout << num << endl;
    if(str.size()-3*num != 47)return false;
    else return true;
}
int main(int argv,char*argc[])
{
    getline(fin,str);
    if(init()&&dfs(str))
    {
        fout << 1 << ' ' << num << endl;
    }
    else fout << 0 << ' ' << 0 << endl;
    fin.close();
    fout.close();
    return 0;
}

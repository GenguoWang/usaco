/*
ID: wanggen3
PROG: cryptcow
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
ifstream fin("cryptcow.in");
ofstream fout("cryptcow.out");
int num;
string str;
string objstr = "Begin the Escape execution at the Break of Dawn";
map<string,int> handled;
bool dfs(string str)
{
    if(handled[str]) return false;
    handled[str] = 1;
    int c[20],o[20],w[20];
    int nc=0,no=0,nw=0;
    int pos=0;
    while((pos=str.find('C',pos))!=string::npos)c[nc++] = pos++;
    if(nc==0)
    {
        if(str == objstr)
            return true;   
        else return false;
    }
    if(str.substr(0,c[0]) != objstr.substr(0,c[0])) return false;
    pos = 0;
    while((pos=str.find('O',pos))!=string::npos)o[no++] = pos++;
    pos = 0;
    while((pos=str.find('W',pos))!=string::npos)w[nw++] = pos++;
    if(str.substr(w[nw-1]+1) != objstr.substr(objstr.size()+w[nw-1]+1-str.size())) return false;
    int lastC = -1;
    int lastO = -1;
    for(int i=0; i < str.size();++i)
    {
        if(str[i]=='C')
        {
            lastC = i;   
            lastO = -1;
        }
        if(str[i]=='O')
        {
            lastO = i;
            if(lastC>=0 && objstr.find(str.substr(lastC+1,i-lastC-1))==string::npos) 
            {
                //cout << str << endl;
                //cout << str.substr(lastC+1,i-lastC-1) << endl;
                return false;    
            }
            lastC = -1;
        }
        if(str[i]=='W')
        {
            if(lastO>=0 && objstr.find(str.substr(lastO+1,i-lastO-1))==string::npos) 
            {
                //cout << str << endl;
                //cout << str.substr(lastO+1,i-lastO-1) << endl;
                return false;    
            }
            lastO = -1;
            lastC = -1;
        }
    }
    for(int j=no-1;j>=0;--j)
    {
        for(int i=nc-1;i>=0;--i)
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

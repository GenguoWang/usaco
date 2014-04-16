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
//#define MOD 35027
int num;
string str;
string objstr = "Begin the Escape execution at the Break of Dawn";
int objsize = 47;
int stepCount;
bool visited[MOD];
vector<vector<int> > vis[MOD];
struct StrList
{  
    StrList():next(NULL),pre(NULL),index(0){}
    StrList *next,*pre;
    int index;
};
bool isVisited(StrList *head,StrList *tail)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    vector<int> res;
    for(StrList * node = head;node != tail;node = node->next)
    {
        hash = (hash<<4) + node->index;
        res.push_back(node->index);
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
            if(res.size() != vis[hash][i].size()) continue;
            bool isEqual = true;
            for(int j=0;j<res.size();++j)
            {
                if(res[j]!=vis[hash][i][j])
                {
                    isEqual = false;
                    break;
                }
            }
            if(isEqual)return true;
        }
        vis[hash].push_back(res);
        return false;   
    }
    else
    {
        visited[hash] = true;
        vis[hash].push_back(res);
        return false;
    }
}
void output(StrList *sl,StrList *el)
{
    while(sl!=el)
    {
        cout << str[sl->index];
        sl = sl->next;
    }
    cout << endl;
}
bool isMatch(StrList *sl,StrList *el)
{
    int strIndex = 0;
    while(sl != el)
    {
        if(str[sl->index] != objstr[strIndex++]) return false;
        sl = sl->next;
    }
    return true;
}
bool isReMatch(StrList *sl,StrList *el)
{
    int strIndex = objstr.size()-1;
    while(sl != el)
    {
        if(str[sl->index] != objstr[strIndex--]) return false;
        sl = sl->pre;
    }
    return true;
}
StrList * createFrom(StrList * (&tail))
{
    StrList *head = new StrList;
    tail = head;
    for(int i=0;i<str.size();++i)
    {
        tail->next = new StrList;
        tail->next->pre = tail;
        tail = tail->next;
        tail->index = i;
    }
    tail->next = new StrList;
    tail->next->pre = tail;
    tail = tail->next;
    return head;
}
void decode(StrList *c,StrList *o,StrList *w)
{
    if(c->next != o && o->next != w)
    {
        c->pre->next = o->next;
        o->next->pre = c->pre;
        o->pre->next = w->next;
        w->next->pre = o->pre;
        w->pre->next = c->next;
        c->next->pre = w->pre;
    }
    else if(c->next == o && o->next == w)
    {
        c->pre->next = w->next;
        w->next->pre = c->pre;
    }
    else if(c->next == o)
    {
        c->pre->next = o->next;
        o->next->pre = c->pre;
        w->pre->next = w->next;
        w->next->pre = w->pre;
    }
    else if(o->next == w)
    {
        c->pre->next = c->next;
        c->next->pre = c->pre;
        o->pre->next = w->next;
        w->next->pre = o->pre;
    }
}
void encode(StrList *c,StrList *o,StrList *w)
{
    c->pre->next = c;
    c->next->pre = c;
    o->pre->next = o;
    o->next->pre = o;
    w->pre->next = w;
    w->next->pre = w;
}
bool findSeg(StrList *sl,StrList *tail)
{
    bool isOK;
    int j;StrList* node;
    for(int i=0;i<objsize;++i)
    {
        isOK = true;
        for(node = sl,j=i;node != tail && j<objsize;node = node->next,j++)
        {
            if(str[node->index] != objstr[j])
            {
                isOK = false;   
                break;
            }
        }
        if(isOK && j<objsize) return true;
    }
    return false;
}
int len(StrList *sl,StrList *tail)
{
    int t = 0;
    while(sl!=tail)
    {
        t++;
        sl = sl->next;
    }
    return t;
}
bool dfs(StrList *sl,StrList *tail,int level=0)
{
    //int ttt = len(sl->next,tail);
    //cout << level << ": len:"<<len(sl->next,tail) <<":";
    //stepCount++;
    //if(stepCount%100000==0) 
    //    cout << stepCount << endl;
    StrList *c[20],*o[20],*w[20],*a[60];
    int cc[20],oo[20],ww[20];
    int nc=0,no=0,nw=0,na=0;
    StrList *i;
    int pos;
    for(i = sl->next,pos=0;i!=tail;i = i->next,pos++)
    {
        if(str[i->index]=='C')
        {
            cc[nc] = pos;
            c[nc++] = i;
            a[na++] = i;
        }
        else if(str[i->index]=='O')
        {
            oo[no] = pos;
            o[no++] = i;
            a[na++] = i;
        }
        else if(str[i->index]=='W')
        {
            ww[nw] = pos;
            w[nw++] = i;
            a[na++] = i;
        }
    }
    if(nc==0)
    {
        if(isMatch(sl->next,tail))
            return true;   
        else return false;
    }
    if(!isMatch(sl->next,c[0])) return false;
    if(!isReMatch(tail->pre,w[nw-1])) return false;
    for(int i=0; i < na-1;++i)
    {
        if(a[i+1]!=a[i]->next && !findSeg(a[i]->next,a[i+1])) 
        {
            return false;    
        }
    }
    if(isVisited(sl->next,tail)) return false;
    for(int i=nc-1;i>=0;--i)
    {
        for(int j=no-1;j>=0;--j)
        {
            for(int k=nw-1;k>=0;--k)
            {
                if(cc[i]<oo[j]&&oo[j]<ww[k])
                {
                    decode(c[i],o[j],w[k]);
                    if(dfs(sl,tail,level+1)) return true;
                    encode(c[i],o[j],w[k]);
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
    if(str.size()-3*num != 47)return false;
    else return true;
}
int main(int argv,char*argc[])
{
    StrList *sl,*tail;
    getline(fin,str);
    sl = createFrom(tail);
    if(init()&&dfs(sl,tail))
    {
        fout << 1 << ' ' << num << endl;
    }
    else fout << 0 << ' ' << 0 << endl;
    fin.close();
    fout.close();
    return 0;
}

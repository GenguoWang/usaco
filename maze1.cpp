/*
ID: wanggen3
PROG: maze1
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("maze1.in");
ofstream fout("maze1.out");
#include <vector>
#include <stack>
#include <queue>
#include <utility>
int main(int argv,char*argc[])
{
    int w,h;
    fin >> w >> h;
    vector<vector<char> > map;
    char tmp[200];
    fin.getline(tmp,200);
    for(int i=0;i<=2*h;++i)
    {
        vector<char> row;
        fin.getline(tmp,200);
        for(int j=0;j<=2*w;++j)
        {
            row.push_back(tmp[j]);
        }
        map.push_back(row);
    }
    int x,y;
    vector<int> node(w*h);
    vector< vector<int> > edge(w*h);
    for(int i=0;i<=h;++i)
    {
        y=2*i;
        for(int j=0; j<w;++j)
        {
            x=2*j+1;
            if(map[y][x]==' ')
            {
                if(i==0)
                {
                    node[i*w+j] = 1;
                }
                else if(i==h)
                {
                    node[(i-1)*w+j] = 1;
                }
                else
                {
                    edge[i*w+j].push_back((i-1)*w+j);
                    edge[(i-1)*w+j].push_back(i*w+j);
                }
            }
        }
    }
    for(int i=0;i<h;++i)
    {
        y=2*i+1;
        for(int j=0;j<=w;++j)
        {
            x=2*j;
            if(map[y][x]==' ')
            {
                if(j==0)
                {
                    node[i*w+j] = 1;
                }
                else if(j==w)
                {
                    node[i*w+j-1] = 1;
                }
                else
                {
                    edge[i*w+j].push_back(i*w+j-1);
                    edge[i*w+j-1].push_back(i*w+j);
                }
            }
        }
    }
    int max=0;
    for(int s=0;s < w*h;++s)
    {
        vector<int> abl(w*h);
        abl[s]=1;
        queue<pair<int,int> > que;
        que.push(make_pair(s,1));
        pair<int,int> top;
        int dist,num;
        while(!que.empty())
        {
            top = que.front();
            que.pop();
            num = top.first;
            dist = top.second;
            if(node[num])
            {
                if(dist>max) max=dist;
                break;
            }
            for(vector<int>::iterator it=edge[num].begin(); it != edge[num].end();++it)
            {
                if(abl[*it]==0)
                {
                    abl[*it]=1;
                    que.push(make_pair(*it,dist+1));
                }
            }
        }
    }
    fout << max<< endl;
    fin.close();
    fout.close();
    return 0;
}

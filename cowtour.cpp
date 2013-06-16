/*
ID: wanggen3
PROG: cowtour
LANG: C++
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;
#define MAX 150
ifstream fin("cowtour.in");
ofstream fout("cowtour.out");
double dist[MAX][MAX];
double minD[MAX];
double getDist(pair<int,int> i, pair<int,int> j)
{
    int x=i.first-j.first;
    int y=i.second-j.second;
    return sqrt(x*x+y*y);
}
int main(int argv,char*argc[])
{
    int N;
    fin >> N;
    int x,y;
    vector <pair<int,int> >node;
    for(int i=0;i<N;++i)
    {
        fin >> x >> y;
        minD[i] = 0;
        node.push_back(make_pair(x,y));
    }
    char flag;
    for(int i=0;i<N;++i)
    {
        for(int j=0;j<N;++j)
        {
            dist[i][j] = 9.9e100;
            fin >> flag;
            if(flag=='1')
            {
                dist[i][j] = getDist(node[i],node[j]);
            }
        }
    }
    for(int k=0;k<N;++k)
    {
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<N;++j)
            {
                if(dist[i][k]+dist[k][j] <dist[i][j])
                {
                    dist[i][j] = dist[i][k]+dist[k][j];
                }
            }
        }
    }
    vector<set<int> > ss;
    vector<double> mm;
    double dtmp;
    set<int> se;
    for(int i=0;i<N;++i)se.insert(i);
    int pot;
    while(!se.empty())
    {
        pot = *(se.begin());
        se.erase(pot);
        set<int> sa;
        sa.insert(pot);
        for(int i=0;i<N;++i)
        {
            if(dist[pot][i]<9e100)
            {
                sa.insert(i);
                se.erase(i);
            }
        }
        dtmp=0;
        for(set<int>::iterator it=sa.begin();it != sa.end();it++) 
        {
            for(set<int>::iterator jt=sa.begin();jt != sa.end();jt++) 
            {
                if(*it==*jt)continue;
                if(dist[*it][*jt]>minD[*it]) minD[*it] = dist[*it][*jt];
                dtmp = max(dist[*it][*jt],dtmp);
            }
        }
        ss.push_back(sa);
        mm.push_back(dtmp);
    }
    double res = 9.9e100;
    int size=ss.size();
    for(int ii=0;ii!=size;++ii)
    {
        set<int> &sa = ss[ii];
        for(int jj=ii+1;jj!=size;++jj)
        {
            set<int> &sb = ss[jj];
            for(set<int>::iterator it=sa.begin();it != sa.end();it++) 
            {
                for(set<int>::iterator jt=sb.begin();jt != sb.end();jt++) 
                {
                    dtmp = minD[*it]+minD[*jt]+getDist(node[*it],node[*jt]);
                    dtmp = max(dtmp,mm[ii]);
                    dtmp = max(dtmp,mm[jj]);
                    if(dtmp < res)
                    {
                        res = dtmp;
                    }
                }
            }

        }
    }
    fout <<fixed <<setprecision(6)<< res << endl;
    fin.close();
    fout.close();
    return 0;
}

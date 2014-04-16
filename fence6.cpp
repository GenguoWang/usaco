/*
ID: wanggen3
PROG: fence6
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
ifstream fin("fence6.in");
ofstream fout("fence6.out");
int g[202][202];
int s[202][202];
int handed[101];
int node1[202],node2[202];
vector<int> edge1[202],edge2[202];
int main(int argv,char*argc[])
{
    memset((void*)g,0x1f,sizeof(g));
    memset((void*)s,0x1f,sizeof(s));
    memset((void*)handed,0,sizeof(handed));
    int N;
    fin >> N;
    int num,len,s1,s2,temp;
    int nodeNum=0;
    for(int i = 0;i<N;++i)
    {
        fin >> num >> len >> s1 >> s2;
        node1[num] = -1;
        node2[num] = -1;
        while(s1--) 
        {
            fin >> temp;
            edge1[num].push_back(temp);
            if(handed[temp])
            {
                if(find(edge1[temp].begin(),edge1[temp].end(),num)!=edge1[temp].end()) node1[num] = node1[temp];
                else node1[num] = node2[temp];
            }
        }
        while(s2--)
        {
            fin >> temp;
            edge2[num].push_back(temp);
            if(handed[temp])
            {
                if(find(edge1[temp].begin(),edge1[temp].end(),num)!=edge1[temp].end()) node2[num] = node1[temp];
                else node2[num] = node2[temp];
            }
        }
        if(node1[num] == -1) node1[num] = nodeNum++;
        if(node2[num] == -1) node2[num] = nodeNum++;
        handed[num] = 1;
        g[node1[num]][node2[num]] = len;
        g[node2[num]][node1[num]] = len;
        s[node1[num]][node2[num]] = len;
        s[node2[num]][node1[num]] = len;
    }
    
    for(int i=0;i<nodeNum;++i)
    {
        for(int j=0;j<nodeNum;++j)
        {
            if(g[i][j]>1000) cout << "0 ";
            else cout << g[i][j] <<' ';
        }
        cout << endl;
    }
    int answer = 0x3f3f3f3f;
    for(int k=0;k<nodeNum;++k)
    {
        for(int i=0;i<k;++i)
        {
            for(int j=i+1;j<k;++j)
            {
                answer = min(answer,s[i][j]+g[i][k]+g[k][j]);
                if(k==11 && i==7 && j==10)
                {
                    cout << "www" << endl;
                    cout << s[i][j] << ' ' << g[i][k] << ' ' << g[k][j] << endl;
                }
            }
        }
        for(int i=0;i<nodeNum;++i)
        {
            for(int j=0;j<nodeNum;++j)
            {
                s[i][j] = min(s[i][j],s[i][k]+s[k][j]);
            }
        }
    }
    fout << answer << endl;
    fin.close();
    fout.close();
    return 0;
}

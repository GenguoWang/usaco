/*
ID: wanggen3
PROG: fence
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
ifstream fin("fence.in");
ofstream fout("fence.out");
int used[501][501];
int degree[501];
vector<priority_queue<int,vector<int>,greater<int> > > nodes(501);
vector<int> result;
void find_euler(int index)
{
    while(degree[index]>0)
    {
        int neighbor;
        do{
            neighbor = nodes[index].top();
            nodes[index].pop();
        }while(used[index][neighbor]==0);
        degree[index]--;
        degree[neighbor]--;
        used[index][neighbor]--;
        used[neighbor][index]--;
        find_euler(neighbor);
    }
    result.push_back(index);
}
int main(int argv,char*argc[])
{
    int F;
    fin >> F;
    int x,y;
    while(F--)
    {
        fin >> x >> y;
        nodes[x].push(y);
        nodes[y].push(x);
        degree[x]++;
        degree[y]++;
        used[x][y]++;
        used[y][x]++;
    }
    int firstIndex = 0;
    for(int i=1;i<=500;++i)
    {
        if(firstIndex==0&&degree[i]>0)firstIndex=i;
        if(degree[i]%2==1)
        {
            firstIndex = i;
            break;
        }
    }
    find_euler(firstIndex);
    for(int i=result.size()-1;i>=0;i--) fout << result[i] << endl;
    fin.close();
    fout.close();
    return 0;
}

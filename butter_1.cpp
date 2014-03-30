/*
ID: wanggen3
PROG: butter
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define MAX 99999999
using namespace std;
ifstream fin("butter.in");
ofstream fout("butter.out");
struct Node
{
    int num,weight;
};
struct greaterNode
{
    bool operator ()(const Node& n1,const Node& n2)
    {
        return n1.weight > n2.weight;
    }
    
};

int main(int argv,char*argc[])
{
    int N,P,C;
    int cow[500];
    int path[800][800];
    int x,y,w;
    fin >> N >> P >> C;
    for(int i=0;i<P;++i)
    {
        for(int j=0;j<P;++j)
        {
            if(i!=j) path[i][j] = MAX;
            else path[i][j] = 0;
        }
    }
    vector<vector<Node> > pastures(P);
    for(int i=0;i<N;++i)fin>>cow[i];
    for(int i=0;i<C;++i)
    {
        fin >> x >> y >> w;
        Node node;
        node.num = y-1;
        node.weight = w;
        pastures[x-1].push_back(node);
        node.num = x-1;
        pastures[y-1].push_back(node);
        path[x-1][y-1] = w;
        path[y-1][x-1] = w;
    }
    for(int i=0;i<P;++i)
    {
        vector<int> visited(P);
        visited[i] = 1;
        priority_queue<Node,vector<Node>,greaterNode> pq;
        for(int j=0;j<pastures[i].size();++j) pq.push(pastures[i][j]);
        while(!pq.empty())
        {
            while(!pq.empty()&&visited[pq.top().num])pq.pop();
            if(pq.empty())break;
            Node currentNode = pq.top();
            int currentNum = currentNode.num;
            int currentWeight = currentNode.weight;
            pq.pop();
            visited[currentNum] = 1;
            for(int j=0;j<pastures[currentNum].size();++j) 
            {
                Node nextNode = pastures[currentNum][j];
                if(path[i][currentNum]+path[currentNum][nextNode.num]
                    < path[i][nextNode.num])
                {
                    path[i][nextNode.num] = path[i][currentNum]+path[currentNum][nextNode.num];
                    nextNode.weight = path[i][nextNode.num];
                    pq.push(nextNode);
                }
            }
        }
    }
    int minCost = MAX,currentCost;
    int minP;
    for(int i=0;i<P;++i)
    {
        currentCost = 0;
        for(int j=0;j<N;++j)
        {
            currentCost += path[cow[j]-1][i];
        }
        if(currentCost<minCost)
        {
            minCost = currentCost;
            minP = i;
        }
    }
    fout << minCost << endl;
    fin.close();
    fout.close();
    return 0;
}

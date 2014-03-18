/*
ID: wanggen3
PROG: agrinet
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAX 99999999
ifstream fin("agrinet.in");
ofstream fout("agrinet.out");
int main(int argv,char*argc[])
{
    int n;
    int graph[100][100];
    int minDistance[100];
    bool isInMST[100];
    int totalCost = 0;
    fin >> n;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            fin >> graph[i][j];
        }
    }
    for(int i=0; i < n; ++i)
    {
        minDistance[i] = MAX;
        isInMST[i] = false;
    }
    minDistance[0] = 0;
    int findMin;
    int findNode;
    for(int i=0; i < n; ++i)
    {
        findMin = MAX;
        for(int j=0; j < n; ++j)
        {
            if(!isInMST[j] && minDistance[j] < findMin)
            {
                findNode = j;
                findMin = minDistance[j];
            }
        }
        isInMST[findNode] = true;
        totalCost += findMin;
        for(int j = 0; j < n; ++j)
        {
            if(minDistance[j] > graph[j][findNode])
            {
                minDistance[j] = graph[j][findNode];
            }
        }
    }
    fout << totalCost << endl;
    fin.close();
    fout.close();
    return 0;
}

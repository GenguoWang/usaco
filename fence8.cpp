/*
ID: wanggen3
PROG: fence8
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("fence8.in");
ofstream fout("fence8.out");
int n,r,mayWaste,waste;
bool hasResult;
int board[50];
int rail[1023];
int myCount;
int maxDepth = 0,total=0;
bool dfs(int depth,int startRail,int startBoard,int preRail)
{
    //cout << "s" << startRail << ' ' << depth << endl;
    myCount++;
    if(depth==0)
    {
        return true;
    }
    int currentWast = 0;
    //int i = maxDepth-depth;
    int i = depth-1;
    for(int j=(preRail==rail[i]?startBoard:0);j<n;++j)
    {
        if(board[j]>=rail[i])
        {
            board[j] -= rail[i];
            if(board[j] < rail[0])
            {
                waste += board[j];
            }
            if(waste<=mayWaste && dfs(depth-1,i+1,j,rail[i]))
            {
                return true;
            }
            if(board[j] < rail[0])
            {
                waste -= board[j];
            }
            board[j] += rail[i];
        }
    }
    return false;
}
int main(int argv,char*argc[])
{
    fin >> n;
    int sum =0;
    for(int i=0;i<n;++i)
    {
        fin >> board[i];
        sum += board[i];
    }
    fin >> r;
    for(int i=0;i<r;++i)
    {
        fin >> rail[i];
    }
    sort(board,board+n);
    sort(rail,rail+r);
    while(maxDepth<r&&total+rail[maxDepth]<=sum)
    {
        total += rail[maxDepth];
        maxDepth++;
    }
    mayWaste = sum - total;
    while(maxDepth)
    {
        cout << maxDepth << ' ' << mayWaste << endl;
        waste = 0;
        myCount = 0;
        if(dfs(maxDepth,0,0,0))break;
        cout << "myCount " << myCount << endl;
        maxDepth--;
        mayWaste += rail[maxDepth];
    }
    cout << maxDepth << endl;
    fout << maxDepth << endl;
    fin.close();
    fout.close();
    return 0;
}

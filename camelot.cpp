/*
ID: wanggen3
PROG: camelot
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
ifstream fin("camelot.in");
ofstream fout("camelot.out");
const int MAX_INT = 99999999;
int board[30][26];
int shortest[781][781];
int x[] = {1,1 ,-1,-1,2, 2,-2,-2};
int y[] = {2,-2, 2,-2,1,-1, 1,-1};
int R,C;
bool avaible(int row,int col)
{
    return row>=0 && row<R
        && col>=0 && col<C
        && board[row][col] == MAX_INT;
}
struct nodeInfo
{
    int row,col,step;
    nodeInfo(int r,int c,int s):row(r),col(c),step(s){}
};
void findShortest(int row,int col)
{
    int currentRow,currentCol,step;
    int nextRow,nextCol;
    queue<nodeInfo> q;
    q.push(nodeInfo(row,col,0));
    board[row][col] = step;
    int cnt=0;
    while(!q.empty())
    {
        currentRow = q.front().row;
        currentCol = q.front().col;
        step = q.front().step;
        board[currentRow][currentCol] = step;
        cnt ++;
        q.pop();
        for(int i=0;i<8;++i)
        {
            nextRow = currentRow+x[i];
            nextCol = currentCol+y[i];
            if(avaible(nextRow,nextCol))
            {
                q.push(nodeInfo(nextRow,nextCol,step+1));
                board[nextRow][nextCol] = MAX_INT-1;
            }
        }
    }
}
int main(int argv,char*argc[])
{
    fin >> R >> C;
    for(int i=0;i<R;++i)
    {
        for(int j=0;j<C;++j)
        {
            for(int r=0;r<R;++r)
                for(int c=0;c<C;++c)board[r][c]=MAX_INT;
            findShortest(i,j);
            for(int r=0;r<R;++r)
                for(int c=0;c<C;++c)shortest[i*C+j][r*C+c] = board[r][c];
        }
    }
    char colChar;
    int row;
    int kingRow,kingCol;
    fin >> colChar >> row;
    kingRow = row-1;
    kingCol = (int)colChar-(int)'A';
    vector<pair<int,int> > knights;
    while(fin >> colChar >> row)
    {
        knights.push_back(make_pair(row-1,(int)colChar-(int)'A'));
    }
    int minStep = MAX_INT;
    int tempStep;
    int minOverCost,minOverTemp;
    for(int r=0;r<R;++r)
    {
        for(int c=0;c<C;++c)
        {
            //cout << "r" << r << "c" << c << endl;
            tempStep = max(abs(kingRow-r),abs(kingCol-c));
            for(vector<pair<int,int> >::iterator it = knights.begin();
                it != knights.end(); ++it)
            {
                tempStep += shortest[r*C+c][it->first*C+it->second];
            }
            if(tempStep < minStep) minStep = tempStep;
            for(int kr=kingRow-2;kr <= kingRow+2;++kr)
            for(int kc=kingCol-2;kc<=kingCol+2;++kc)
            {
                if(kr<0||kc<0||kr>=R||kc>=C)continue;
                minOverCost = MAX_INT;
                for(vector<pair<int,int> >::iterator it = knights.begin();
                    it != knights.end(); ++it)
                {
                    minOverTemp = shortest[r*C+c][kr*C+kc]+shortest[kr*C+kc][it->first*C+it->second]-shortest[r*C+c][it->first*C+it->second];
                    if(minOverTemp < minOverCost) minOverCost = minOverTemp;
                }
                tempStep = max(abs(kingRow-kr),abs(kingCol-kc))+minOverCost;
                for(vector<pair<int,int> >::iterator it = knights.begin();
                    it != knights.end(); ++it)
                {
                    tempStep += shortest[r*C+c][it->first*C+it->second];
                }
                if(tempStep < minStep) minStep = tempStep;
            }
        }
    }
    fout << minStep << endl;
    fin.close();
    fout.close();
    return 0;
}

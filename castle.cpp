/*
ID: wanggen3
PROG: castle
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
struct Edge
{
    int type;
    int x,y;
	int px,py;
	int dirt;
};
struct Wall
{
	int x,y;
	int type;
};
vector<Edge> edges[51][51];
int visited[51][51];
int compnent[51][51];
//int connect[2600][2600];
Wall wall;
int maxSize;
int compsize[2600];
int comp;
int M,N;
void dfs(int x,int y,bool flag)
{
	int tcomp;
    if(!flag)
	{
		compnent[x][y] = comp;
	}else
	{
		tcomp = compnent[x][y];
	}
	visited[x][y] = 1;
	vector<Edge> &v = edges[x][y];
	for(int i=0; i <v.size(); ++i)
	{
		if(v[i].type==0 && !visited[v[i].x][v[i].y])
		{
			dfs(v[i].x,v[i].y,flag);
		}
		else if(v[i].type==1)
		{
			
			if(flag && compnent[v[i].x][v[i].y]!=tcomp)
			{
				int cmp = compnent[v[i].x][v[i].y];
				if(compsize[cmp]+compsize[tcomp]>maxSize)
				{
					Wall w1;
					if(v[i].dirt == 0 || v[i].dirt == 2)
					{
						w1.x = v[i].x;w1.y = v[i].y; w1.type=3-v[i].dirt;
					}
					else
					{
						w1.x = x;w1.y=y;w1.type=v[i].dirt;
					}
					wall = w1;
					maxSize = compsize[cmp]+compsize[tcomp];
				}
				else if(compsize[cmp]+compsize[tcomp]==maxSize)
				{
					Wall w1;
					if(v[i].dirt == 0 || v[i].dirt == 2)
					{
						w1.x = v[i].x;w1.y = v[i].y; w1.type=3-v[i].dirt;
					}
					else
					{
						w1.x = x;w1.y=y;w1.type=v[i].dirt;
					}
					Wall w2 = wall;
					if(w1.y < w2.y)
					{
						wall = w1;
					}
					else if(w1.y == w2.y && w1.x > w2.x)
					{
						wall = w1;
					}
					else if(w1.y == w2.y && w1.x == w2.x && w1.type==1)
					{
						wall = w1;
					}
					maxSize = compsize[cmp]+compsize[tcomp];
				}
				
			}
		}
	}
}
ifstream fin("castle.in");
ofstream fout("castle.out");
int main(int argv,char*argc[])
{
    fin >> M >> N;
	int temp;
	Edge tedge;
	for(int i=1; i <= N;++i)
	{
		for(int j=1; j <= M; ++j)
		{
			fin >> temp;
			//west
			if(temp&1)
			{
				if(j>1)
				{
					tedge.x = i;
					tedge.y = j-1;
					tedge.type = 1;//墙
					tedge.dirt = 0;
					edges[i][j].push_back(tedge);
				}
			}
			else
			{
				tedge.x = i;
				tedge.y = j-1;
				tedge.type = 0;//通
				edges[i][j].push_back(tedge);
			}
			//north
			if(temp&2)
			{
				if(i>1)
				{
					tedge.x = i-1;
					tedge.y = j;
					tedge.type = 1;//墙
					tedge.dirt = 1;
					edges[i][j].push_back(tedge);
				}
			}
			else
			{
				tedge.x = i-1;
				tedge.y = j;
				tedge.type = 0;//通
				edges[i][j].push_back(tedge);
			}
			//east
			if(temp&4)
			{
				if(j<M)
				{
					tedge.x = i;
					tedge.y = j+1;
					tedge.type = 1;//墙
					tedge.dirt = 3;
					edges[i][j].push_back(tedge);
				}
			}
			else
			{
				tedge.x = i;
				tedge.y = j+1;
				tedge.type = 0;//通
				edges[i][j].push_back(tedge);
			}
			//south
			if(temp&8)
			{
				if(i<N)
				{
					tedge.x = i+1;
					tedge.y = j;
					tedge.type = 1;//墙
					tedge.dirt = 2;
					edges[i][j].push_back(tedge);
				}
			}
			else
			{
				tedge.x = i+1;
				tedge.y = j;
				tedge.type = 0;//通
				edges[i][j].push_back(tedge);
			}
		}
	}
	memset((void*)compnent,0,sizeof(compnent));
	memset((void*)visited,0,sizeof(visited));
	comp = 0;
	for(int i=1; i <= N; ++i)
	{
		for(int j=1; j <= M; ++j)
		{
			if(!visited[i][j])
			{
				comp++;
				dfs(i,j,false);
			}
		}
	}
	memset((void*)compsize,0,sizeof(compsize));
	int cx[2600],cy[2600];
	for(int i=1;i<=N;++i)
	{
		for(int j=1;j<=M;++j)
		{
			compsize[compnent[i][j]]++;
			cx[compnent[i][j]] = i;
			cy[compnent[i][j]] = j;
		}
	}
	int max=0;
	maxSize = 0;
	memset((void*)visited,0,sizeof(visited));
	for(int i=1; i <= comp; ++i)
	{
		if(compsize[i]>max) max = compsize[i];
		dfs(cx[i],cy[i],true);
	}
	/*
	for(int i=1; i < comp; ++i)
	{
		for(int j=i+1; j <= comp; ++j)
		{
			if(compsize[i]+compsize[j]>maxd&&(connect[i][j]||connect[j][i]))
			{
				maxd = compsize[i] + compsize[j];
				c1 =i;
				c2 = j;
			}
		}
	}
	int i,j;
	bool ttt = false;
	for(i=1;i<=N;++i)
	{
		for(j=1;j<=M;++j)
		{
			if(compnent[i][j]==c1) 
			{
				ttt= true;
				break;
			}
		}
		if(ttt) break;
	}
	memset((void*)visited,0,sizeof(visited));
	memset((void*)connect,0,sizeof(connect));
	dfs(i,j,true,c2);
	*/
	fout << comp << endl;
	fout << max << endl;
	fout << maxSize << endl;
	fout << wall.x << " " << wall.y << " ";
	switch(wall.type)
	{
	case 0:fout<<'W'<< endl;
		break;
	case 1:fout<<'N'<< endl;
		break;
	case 2:fout<<'S'<< endl;
		break;
	case 3:fout<<'E'<< endl;
		break;
	}
    fin.close();
    fout.close();
    return 0;
}
/*
ID: wanggen3
PROG: butter
LANG: C++
*/
#include <list>
#include <queue>
#include <set>
#include <utility>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#define MAX 99999999
using namespace std;
namespace kingo
{
template<typename DataType,typename ContainType=vector<DataType>,typename CompType=less<DataType> >
class heap
{
	private:
        static const int INVALID_INDEX = -1;
        ContainType data;
        vector<int> dataIndex;
        vector<int> invertIndex;
        int mSize;
        CompType compare;
        int left(int index) { return 2*index; }
        int right(int index) { return 2*index+1; }
        int parent(int index) { return index/2; }
        void swap(int i,int j)
        {
            DataType temp;
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            
            //change index
            int pi = invertIndex[i];
            int pj = invertIndex[j];
            int tempIndex = dataIndex[pi];
            dataIndex[pi] = dataIndex[pj];
            dataIndex[pj] = tempIndex;
            
            //change inverted index
            tempIndex = invertIndex[i];
            invertIndex[i] = invertIndex[j];
            invertIndex[j] = tempIndex;
        }
        void heapify(int index)
        {
            int l = left(index),r = right(index);
            int theIndexOfUpper = index;
            if(l<=mSize && compare(data[l],data[theIndexOfUpper]))
            {
                theIndexOfUpper = l;
            }
            if(r<=mSize && compare(data[r],data[theIndexOfUpper]))
            {
                theIndexOfUpper = r;
            }
            if(index != theIndexOfUpper)
            {
                swap(index,theIndexOfUpper);
                heapify(theIndexOfUpper);
            }
        }
        void initEmptyHeap()
        {
            mSize = 0;
            DataType zeroPos;
            data.push_back(zeroPos);
            dataIndex.push_back(0);
            invertIndex.push_back(0);
        }
        int addData(const DataType& newData)
        {
            int thisIndex;
            mSize++;
            if(mSize < data.size())
            {
                data[mSize] = newData;
                dataIndex.push_back(mSize);
                thisIndex = dataIndex.size()-1;
                invertIndex[mSize] = thisIndex;
            }
            else
            {
                data.push_back(newData);   
                dataIndex.push_back(mSize);
                thisIndex = dataIndex.size()-1;
                invertIndex.push_back(thisIndex);
            }
            return dataIndex.size()-1;
        }
        void removeLast()
        {
            dataIndex[invertIndex[mSize]] = INVALID_INDEX;
            invertIndex[mSize] = INVALID_INDEX;
            mSize--;
        }
        void changeUp(int i)
        {
            while(i > 1 && compare(data[i],data[parent(i)]))
            {
                swap(i,parent(i));
                i = parent(i);
            }
        }
    public:
        heap()
        {
            initEmptyHeap();
        }
        template<typename iterator>
        heap(iterator begin,iterator end)
        {
            initEmptyHeap();
            while(begin != end)
            {
                addData(*begin);
                ++begin;
            }
            build();
        }
        ~heap()
        {
        }
        int size()
        {
            return mSize;
        }
        void build()
        {
            for(int i= mSize/2; i >=1;--i)
            {
                heapify(i);
            }
        }
        void sort()
        {
            for(int last= mSize; last > 1; last--)
            {
                swap(1,last);
                removeLast();
                heapify(1);
            }
            removeLast();
        }
        DataType top()
        {
            return data[1];
        }
        DataType pop()
        {
            DataType topData = data[1];
            swap(1,mSize);
            removeLast();
            heapify(1);
            return topData;
        }
        int push(DataType newData)
        {
            int thisIndex = addData(newData);
            changeUp(mSize);
            return thisIndex;
        }
        void change(int index,DataType newData)
        {
            int pos = dataIndex[index];
            DataType oldData = data[pos];
            data[pos] = newData;
            if(compare(newData,oldData))
            {
                changeUp(pos);
            }
            else
            {
                heapify(pos);
            }
        }
        void changeUpByIndex(int index)
        {
            int pos = dataIndex[index];
            changeUp(pos);
        }
        void changeDownByIndex(int index)
        {
            int pos = dataIndex[index];
            heapify(pos);
        }
        ContainType& getData()
        {
            return data;
        }
        DataType getByIndex(int index)
        {
            int pos = dataIndex[index];
            return data[pos];
        }
        bool isIndexValid(int index)
        {
            if(index>=1 && index < dataIndex.size() && dataIndex[index] != INVALID_INDEX)
            {
                return true;
            }
            else return false;
        }
};
}
namespace kingo
{

struct Vertex;

struct Edge
{
    int weight;
    int s;
    int vertex;
};

struct Vertex
{
    int number;
    int heapIndex;
    int state;
    int weight;
    int dist, pre;
    int dTime,fTime;
    list<Edge> edge; 
};

class Graph{
private:
	int time;
public:
	typedef pair<int,int> tPair;
    typedef vector<Vertex> tV;
    typedef list<Edge> tE;
    typedef tV::iterator tVIter;
    typedef tE::iterator tEIter;
	static const int MAXINT = 0x3ffffff;
	int * shortest;
	vector<Vertex> vertex;
	enum State{NOT_VISITED,VISITING,VISITED};

	Graph(int n)
	{
		vertex.resize(n);
        for(int i=0;i<n;++i) vertex[i].number=i;
		shortest = 0;
	}
	~Graph()
	{
		if(shortest) delete [] shortest;
	}
	
	
	void addDirectEdge(int s,int e,int weight)
	{
		Edge edge;
		edge.vertex = e;
		edge.weight = weight;
		vertex[s].edge.push_back(edge);
	}

	void addEdge(int s,int e,int weight)
	{
		Edge edge;
        edge.s = s;
		edge.vertex = e;
		edge.weight = weight;
		vertex[s].edge.push_back(edge);

        edge.s = e;
		edge.vertex = s;
		edge.weight = weight;
		vertex[e].edge.push_back(edge);
	}
    void BFS()
    {
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->state = NOT_VISITED;
			it->dist = MAXINT;
			it->pre = -1;
		}
		for(int i = 0; i != vertex.size(); ++i)
		{
			if(vertex[i].state == NOT_VISITED)
			{
				BFS_VISIT(i);
			}
		}
    }
	void BFS_VISIT(int s)
	{
		vertex[s].state = VISITING;
		vertex[s].dist = 0;
		vertex[s].pre = -1;
		queue<Vertex *> q;
		q.push(&(vertex[s]));
		Vertex* currentVertex;
		while(!q.empty())
		{
			currentVertex = q.front();
			q.pop();
            tE &currentEdges = currentVertex->edge;
			for(tEIter it = currentEdges.begin(); it != currentEdges.end(); ++it)
			{
                Vertex &nextVertex = vertex[it->vertex];
				if(nextVertex.state == NOT_VISITED)
				{
					nextVertex.state = VISITING;
					nextVertex.dist = currentVertex->dist+1;
					nextVertex.pre = currentVertex->number;
					q.push(&nextVertex);
				}
			}
			currentVertex->state = VISITED;
		}
	}
	void DFS()
	{
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->state = NOT_VISITED;
			it->pre = -1;
		}
		time = 0;
		for(int it = 0; it != vertex.size(); ++it)
		{
			if(vertex[it].state == NOT_VISITED)
			{
				DFS_VISIT(it);
			}
		}
	}
	void DFS_VISIT(int u)
	{
		time++;
		vertex[u].dTime = time;
		vertex[u].state = VISITING;
		for(tEIter it = vertex[u].edge.begin(); it !=vertex[u].edge.end();++it)
		{
            Vertex &nextVertex = vertex[it->vertex];
			if(nextVertex.state == NOT_VISITED)
			{
				nextVertex.pre = u;
				DFS_VISIT(nextVertex.number);
			}
		}
		vertex[u].state = VISITED;
		time++;
		vertex[u].fTime = time;
	}
	static bool topoBigger(Vertex* a, Vertex*b)
	{
		return a->fTime > b->fTime;
	}
	vector<Vertex*> Topological_sort()
	{
		//more efficient way is to make the list in DFS():insert the vertex onto the front of list when setting its fTime
		DFS();
		vector<Vertex*> topo(vertex.size());
		for(int i=0; i < vertex.size(); ++i)
		{
			topo[i] = &(vertex[i]);
		}
		sort(topo.begin(),topo.end(),topoBigger);
        /*
		for(int i=0; i < topo.size(); ++i)
		{
			cout << "Vertex:\t" << topo[i]->number << endl;
			cout << "state:\t" << topo[i]->state << endl;
			cout << "dist:\t" << topo[i]->dist << endl;
			cout << "dTime:\t" << topo[i]->dTime << endl;
			cout << "fTime:\t" << topo[i]->fTime << endl;
			cout << "pre:\t" << topo[i]->pre << endl;
			cout << endl;
		}
        */
        return topo;
	}
	struct lessKey
	{
		bool operator() (Vertex * const &a, Vertex * const &b)
		{
			return a->weight < b->weight;
		}
	};
	void Mst_Prim(int r)
	{
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->weight = MAXINT;
			it->pre = -1;
			it->state = NOT_VISITED;
            it->heapIndex = -1;
		}
		vertex[r].weight = 0;
		heap<Vertex*,vector<Vertex*>,lessKey> q;
        vertex[r].heapIndex = q.push(&(vertex[r]));
		Vertex * pV;
		while(q.size() > 0)
		{
			pV = q.pop();
			pV->state = VISITED;
			for(tEIter eit = pV->edge.begin(); eit != pV->edge.end(); ++eit)
			{
                Vertex &nextVertex = vertex[eit->vertex];
				if(nextVertex.state == NOT_VISITED 
					&& eit->weight < nextVertex.weight)
				{
					nextVertex.weight = eit->weight;
					nextVertex.pre = pV->number;
					if(nextVertex.heapIndex==-1) nextVertex.heapIndex = q.push(&nextVertex);
                    else q.changeUpByIndex(nextVertex.heapIndex);
				}
			}
		}
	};
	void Dijkstra(int s)
	{
		//result is stored in vertex.weight
		for(tVIter it = vertex.begin(); it != vertex.end(); ++it)
		{
			it->weight = MAXINT;
			it->pre = -1;
			it->state = NOT_VISITED;
            it->heapIndex = -1;
		}
		vertex[s].weight = 0;
		heap<Vertex*,vector<Vertex*>,lessKey> q;
		vertex[s].heapIndex = q.push(&(vertex[s]));
		Vertex * pV;
		while(q.size() > 0)
		{
			pV = q.pop();
			pV->state = VISITED;
			for(tEIter eit = pV->edge.begin(); eit != pV->edge.end(); ++eit)
			{
                Vertex &nextVertex = vertex[eit->vertex];
				if(nextVertex.state == NOT_VISITED 
					&& pV->weight + eit->weight < nextVertex.weight)
				{
					nextVertex.weight = pV->weight + eit->weight; 
					nextVertex.pre = pV->number;
					if(nextVertex.heapIndex==-1)
                    {
                        nextVertex.heapIndex = q.push(&nextVertex);
                    }
                    else
                    {
                        q.changeUpByIndex(nextVertex.heapIndex);   
                    }
				}
			}
		}
	}
	int* Floyd()
	{
		int n = vertex.size();
		if(shortest) delete [] shortest;
		shortest = new int[n*n];
		for(int i = 0; i < n; ++i)
		{
			for(int j=0; j < n; ++j)
			{
				if(i==j) shortest[i*n+j] = 0;
				else  shortest[i*n+j] = MAXINT;
			}
		}
        for(int i=0;i < vertex.size();++i)
        {
            for(tEIter eit = vertex[i].edge.begin();eit != vertex[i].edge.end();++eit)
            {
                shortest[i * n + eit->vertex] = eit->weight;
            }
        }
		for(int k = 0; k < n; ++k)
		{
			for(int i = 0; i < n; ++i)
			{
				if(k==i) continue;
				for(int j = 0; j < n; ++j)
				{
					if(shortest[i*n+k] + shortest[k*n+j] < shortest[i*n+j])
					{
						shortest[i*n+j] = shortest[i*n+k] + shortest[k*n+j];
					}
				}
			}
		}
        return shortest;
	}
	void printVertex()
	{
		for(int i=0; i < vertex.size(); ++i)
		{
			cout << "Vertex:\t" << i << endl;
			cout << "state:\t" << vertex[i].state << endl;
			cout << "dist:\t" << vertex[i].dist << endl;
			cout << "dTime:\t" << vertex[i].dTime << endl;
			cout << "fTime:\t" << vertex[i].fTime << endl;
			cout << "pre:\t" << vertex[i].pre << endl;
			cout << endl;
		}
	}
};
}

ifstream fin("butter.in");
ofstream fout("butter.out");
int main(int argv,char*argc[])
{
    int N,P,C;
    int cow[500];
    int x,y,w;
    fin >> N >> P >> C;
    for(int i=0;i<N;++i)fin>>cow[i];
    kingo::Graph graph(P);
    for(int i=0;i<C;++i)
    {
        fin >> x >> y >> w;
        graph.addEdge(x-1,y-1,w);
    }
    int * path = new int[P*P];
    for(int i=0;i<P;++i)
    {
        graph.Dijkstra(i);
        for(int j=0;j<P;++j) path[i*P+j] = graph.vertex[j].weight;
    }
    int minCost = MAX,currentCost;
    int minP;
    for(int i=0;i<P;++i)
    {
        currentCost = 0;
        for(int j=0;j<N;++j)
        {
            currentCost += path[(cow[j]-1)*P+i];
        }
        if(currentCost<minCost)
        {
            minCost = currentCost;
            minP = i;
        }
    }
    fout << minCost << '\n';
    fin.close();
    fout.close();
    return 0;
}

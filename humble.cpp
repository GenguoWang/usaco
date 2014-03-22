/*
ID: wanggen3
PROG: humble
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;
ifstream fin("humble.in");
ofstream fout("humble.out");
int main(int argv,char*argc[])
{
    unsigned int K, N;
    unsigned int value[100];
    fin >> K >> N;
    priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int> > *pq;
    pq = new priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int> >();
    for (int i= 0; i < K; ++i)
    {
        fin >> value[i];
    }
    unsigned int lastNumber = 1;
    unsigned int tempNumber;
    unsigned int testForOverflow;
    for(int i = 1; i <= N; ++i)
    {
        if (pq->size()> 10 * N)
        {
            priority_queue<unsigned int, vector<unsigned int>, std::greater<unsigned int> > * tempPQ = new priority_queue<unsigned int, vector<unsigned int>, std::greater<unsigned int> >;
            int minNumber = N - i + 1;
            int lastTemp = 0;
            tempNumber = lastTemp;
            while (minNumber-- > 0)
            {
                while (tempNumber == lastTemp && !pq->empty())
                {
                    tempNumber = pq->top();
                    pq->pop();
                }
                if (tempNumber == lastTemp) break;
                tempPQ->push(tempNumber);
                lastTemp = tempNumber;
            }
            delete pq;
            pq = tempPQ;
        }
        for (int j = 0; j < K; ++j)
        {
            testForOverflow = value[j]*lastNumber;
            if(testForOverflow/lastNumber == value[j])
            {
                pq->push(testForOverflow);
            }
        }
        tempNumber = lastNumber;
        while(tempNumber == lastNumber)
        {
            tempNumber = pq->top();
            pq->pop();
        }
        lastNumber = tempNumber;
    }
    fout << lastNumber << endl;
    delete pq;
    fin.close();
    fout.close();
    return 0;
}

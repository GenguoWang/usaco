/*
ID: wanggen3
PROG: contact
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class element
{
    public:
    int content;
    int count;
    string cnt;
    element():count(0){
    }
};
ifstream fin("contact.in");
ofstream fout("contact.out");
bool cmp(const element& e1, const element& e2)
{
    return (e1.count > e2.count)
        ||(e1.count == e2.count && e1.content < e2.content);
}
string toStr(int val)
{
    string s;
    while(val > 1)
    {
        s = (char)('0'+(val%2))+s;
        val /= 2;
    }
    return s;
}
int main(int argv,char*argc[])
{
    int A,B,N;
    fin >> A >> B >> N;
    string content;
    string temp;
    vector<element> counter(1<<13);
    for(int i=0;i< (1<<13); ++i) counter[i].content = i;
    while(fin >> temp) content += temp;
    for(int i=A; i <=B;++i)
    {
        for(int j=0; j <= (int)content.size()-i; ++j)
        {
            int value=1;
            for(int k=0; k < i; ++k)
            {
                value = value*2 + (content[j+k]-'0');
            }
            counter[value].count++;
        }
    }
    sort(counter.begin(),counter.end(),cmp);
    int outputCount=0;
    int preCount = 0;
    int i=0;
    int lineCounter;
    while(i < counter.size() && outputCount <= N)
    {
        if(counter[i].count==preCount)
        {
            if(lineCounter%6==0)
                fout <<endl<< toStr(counter[i].content);
            else
                fout <<" "<< toStr(counter[i].content);
            lineCounter++;
        }
        else
        {
            outputCount++;
            lineCounter=1;
            if(outputCount > N || counter[i].count==0)break;
            preCount = counter[i].count;
            if(outputCount>1)
            {
                fout << endl;   
            }
            fout << counter[i].count << endl;
            fout << toStr(counter[i].content);
        }
        i++;
    }
    fout << endl;
    fin.close();
    fout.close();
    return 0;
}

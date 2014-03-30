/*
ID: wanggen3
PROG: shopping
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
using namespace std;
ifstream fin("shopping.in");
ofstream fout("shopping.out");
struct SpecialOffer
{
    vector<pair<int,int> > numberOfProduct; 
    int cost;
    int state;
    void addProduct(int produceID,int number)
    {
        numberOfProduct.push_back(make_pair(produceID,number));
    }
    bool isInTheMapAndConvert(map<int,int>& productToIndex)
    {
        for(int i=0; i < numberOfProduct.size();i++)
        {
            if(productToIndex.count(numberOfProduct[i].first)==0)
                return false;
            numberOfProduct[i].first = productToIndex[numberOfProduct[i].first];
        }
        return true;
    }
};
class State
{
    private:
    vector<int> numbers;
    vector<int> factor;
    int lastFactor;
    public:
    State()
    {
        factor.push_back(1);
        lastFactor = 1;
    }
    void addNumber(int number)
    {
        numbers.push_back(number);
        lastFactor *= number+1;
        factor.push_back(lastFactor);
    }
    int getFinalState()
    {
        int finalState = 0;
        int factor = 1;
        for(int i=0;i<numbers.size();++i)
        {
            finalState += numbers[i]*factor;
            factor *= numbers[i]+1;
        }
        return finalState;
    }
    int getState(int state,vector<pair<int,int> >& numberOfProduct)
    {
        int result=0;
        for(int i=0;i<numberOfProduct.size();++i)
        {
            int index = numberOfProduct[i].first;
            int number = numberOfProduct[i].second;
            int numberInState = (state%factor[index+1])/factor[index];
            if(numberInState < number) return 0;
            result += number*factor[index];
        }
        return result;
    }
    int getCost(int state,vector<int> &costOfProduct)
    {
        int result = 0;
        for(int i=numbers.size()-1;i>=0;--i)
        {
            result += state/factor[i]*costOfProduct[i];
            state = state%factor[i];
        }
        return result;
    }
};
int main(int argv,char*argc[])
{
    int s,n,number,produceID,cost;
    vector<SpecialOffer> specialOffers;
    fin >> s;
    while(s--)
    {
        fin >> n;
        SpecialOffer offer;
        while(n--)
        {
            fin >> produceID >> number;
            offer.addProduct(produceID,number);
        }
        fin >> cost;
        offer.cost = cost;
        specialOffers.push_back(offer);
    }
    int b;
    fin >> b;
    vector<int> costOfProduct;
    vector<int> numberOfProduct;
    map<int,int> productToIndex;
    State state;
    int index=0;
    while(b--)
    {
        fin >> produceID >> number >> cost;
        productToIndex[produceID] = index++;
        numberOfProduct.push_back(number);
        costOfProduct.push_back(cost);
        state.addNumber(number);
    }
    vector<SpecialOffer> convertedOffers;
    for(int i=0;i<specialOffers.size();++i)
    {
        if(specialOffers[i].isInTheMapAndConvert(productToIndex))
        {
            convertedOffers.push_back(specialOffers[i]);
        }
    }
    int finalState = state.getFinalState();
    vector<int> result(finalState+1);
    for(int i=0;i<=finalState;++i) result[i] = state.getCost(i,costOfProduct);
    for(int i=0;i<convertedOffers.size();++i)
    {
        for(int iState=1; iState <= finalState; ++iState)
        {
            int stateInOffer = state.getState(iState,convertedOffers[i].numberOfProduct);
            if(stateInOffer>0&&result[iState-stateInOffer]+convertedOffers[i].cost < result[iState]) result[iState] = result[iState-stateInOffer]+convertedOffers[i].cost;
        }
    }
    fout << result[finalState] << endl;
    fin.close();
    fout.close();
    return 0;
}

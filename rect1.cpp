/*
ID: wanggen3
PROG: rect1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
ifstream fin("rect1.in");
ofstream fout("rect1.out");
class Rect;
list<Rect*> rects;
bool isValid(int llx, int lly, int urx, int ury)
{
    return urx > llx and ury > lly;
}
class Rect
{
public: 
    int llx;
    int lly;
    int urx;
    int ury;
    int color;
    Rect(int llx,int lly,int urx,int ury,int color)
    {
        this->llx = llx;
        this->lly = lly;
        this->urx = urx;
        this->ury = ury;
        this->color = color;
    }
    bool isOverLapWith(Rect* rect)
    {
        return rect->ury > this->lly
            and this->ury > rect->lly
            and rect->urx > this->llx
            and this->urx > rect->llx;
    }
    void splitBy(Rect* rect)
    {
        if(!this->isOverLapWith(rect))return;
        int llx,lly,urx,ury;
        //case 1
        llx = this->llx;
        lly = this->lly;
        urx = rect->llx;
        ury = this->ury;
        if(isValid(llx,lly,urx,ury))
        {
            rects.push_back(new Rect(llx,lly,urx,ury,this->color));
        }
        

        //case 2
        llx = rect->urx;
        lly = this->lly;
        urx = this->urx;
        ury = this->ury;
        if(isValid(llx,lly,urx,ury))
        {
            rects.push_back(new Rect(llx,lly,urx,ury,this->color));
        }

        //case 3
        llx = max(rect->llx, this->llx);
        lly = rect->ury;
        urx = min(rect->urx, this->urx);
        ury = this->ury;
        if(isValid(llx,lly,urx,ury))
        {
            rects.push_back(new Rect(llx,lly,urx,ury,this->color));
        }

        //case 4
        llx = max(rect->llx, this->llx);
        lly = this->lly;
        urx = min(rect->urx, this->urx);
        ury = rect->lly;
        if(isValid(llx,lly,urx,ury))
        {
            rects.push_back(new Rect(llx,lly,urx,ury,this->color));
        }
    }
    int area()
    {
        return (urx-llx)*(ury-lly);
    }
};
void testOverLap()
{
    Rect *a = new Rect(5,5,10,10,1);
    assert(a->isOverLapWith(new Rect(6,6,7,7,1)));
    assert(a->isOverLapWith(new Rect(9,9,11,11,1)));
    assert(!a->isOverLapWith(new Rect(10,10,11,11,1)));
    assert(!a->isOverLapWith(new Rect(5,10,11,11,1)));
    assert(!a->isOverLapWith(new Rect(1,0,3,4,1)));
    //assert(Rect(1,0,3,4,1).isValid());
    //assert(!Rect(4,0,3,4,1).isValid());
}
int main(int argv,char*argc[])
{
    int A, B, N;
    int llx,lly,urx,ury,color;
    fin >> A >> B >> N;
    testOverLap();
    rects.push_back(new Rect(0,0,A,B,1));
    Rect *newRect,*curRect;
    list<Rect*>::iterator begin,end;
    while(N--)
    {
        fin >> llx >> lly >> urx >> ury >> color;
        newRect = new Rect(llx,lly,urx,ury,color);
        rects.push_back(newRect);
        begin = rects.begin();
        while(*begin!=newRect)
        {
            curRect = *begin;
            if(curRect->isOverLapWith(newRect))
            {
                curRect->splitBy(newRect);
                begin = rects.erase(begin);
            }
            else
            {
                begin++;
            }
        }
    }
    vector<int> colors(2501);
    for(begin = rects.begin();begin != rects.end();++begin)
    {
        curRect = *begin;
        colors[curRect->color] += curRect->area();
    }
    for(int i=1; i < 2500; ++i)
    {
        if(colors[i]>0)
        {
            fout << i << ' ' << colors[i] << endl;
        }
    }
    fin.close();
    fout.close();
    return 0;
}

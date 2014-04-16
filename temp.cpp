#include <iostream>
#include <cassert>
using namespace std;
string str;
string objstr;
struct StrList
{  
    StrList *next,*pre;
    int index;
};
bool isMatch(StrList *sl,StrList *el)
{
    int strIndex = 0;
    while(sl != el)
    {
        cout << str[sl->index] << ' '<< objstr[strIndex] << endl;
        if(str[sl->index] != objstr[strIndex++]) return false;
        sl = sl->next;
    }
    return true;
}
bool isReMatch(StrList *sl,StrList *el)
{
    int strIndex = objstr.size()-1;
    while(sl != el)
    {
        cout << str[sl->index] << ' '<< objstr[strIndex] << endl;
        if(str[sl->index] != objstr[strIndex--]) return false;
        sl = sl->pre;
    }
    return true;
}
StrList * createFrom(StrList * (&tail))
{
    StrList *head = new StrList;
    tail = head;
    for(int i=0;i<str.size();++i)
    {
        tail->next = new StrList;
        tail->next->pre = tail;
        tail = tail->next;
        tail->index = i;
    }
    tail->next = new StrList;
    tail->next->pre = tail;
    tail = tail->next;
    return head;
}
void decode(StrList *c,StrList *o,StrList *w)
{
    if(c->next != o && o->next != w)
    {
        c->pre->next = o->next;
        o->pre->next = w->next;
        w->pre->next = c->next;
    }
    else if(c->next == o && o->next == w)
    {
        c->pre->next = w->next;
    }
    else if(c->next == o)
    {
        c->pre->next = o->next;
        w->pre->next = w->next;
    }
    else if(o->next == w)
    {
        c->pre->next = c->next;
        o->pre->next = w->next;
    }
}
void encode(StrList *c,StrList *o,StrList *w)
{
    c->pre->next = c;
    o->pre->next = o;
    w->pre->next = w;
}
void output(StrList *sl,StrList *el)
{
    while(sl!=el)
    {
        cout << str[sl->index];
        sl = sl->next;
    }
    cout << endl;
}
int main()
{
    str = "0123456789";
    objstr = "0123456789";
    StrList *tail;
    StrList *sl = createFrom(tail);
    assert(isMatch(sl->next,tail));
    str = "0123CO4W56789";
    sl = createFrom(tail);
    StrList *c,*o,*w;
    for(StrList* i = sl;i!= NULL;i = i->next)
    {
        if(str[i->index] == 'C') c = i;
        if(str[i->index] == 'O') o = i;
        if(str[i->index] == 'W') w = i;
    }
    assert(isMatch(sl->next,c));
    assert(isReMatch(tail->pre,w));
    decode(c,o,w);
    cout << "ee" << endl;
    assert(isMatch(sl->next,tail));
    encode(c,o,w);
    output(sl->next,tail);
    return 0;
}

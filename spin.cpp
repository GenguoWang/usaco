/*
ID: wanggen3
PROG: spin
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("spin.in");
ofstream fout("spin.out");
struct wedge
{
    int angle;
    int width;
    bool pass(int addAngle, int angle)
    {
        int beginAngle = (this->angle+addAngle)%360;
        return (beginAngle<=angle && angle <= beginAngle+width)
        || (beginAngle+width>=360 and angle <= beginAngle+width-360);
    }
};
class wheel
{
    public:
    int speed;
    vector<wedge> wedges;
    bool pass(int time, int angle)
    {
        for(int i=0; i<wedges.size();++i)
        {
            if(wedges[i].pass(time*speed,angle))return true;
        }
        return false;
    }
};
int main(int argv,char*argc[])
{
    vector<wheel> wheels;
    int n;
    for(int i=0; i < 5; ++i)
    {
        wheel w;
        fin >> w.speed >> n;
        while(n--)
        {
            wedge d;
            fin >> d.angle >> d.width;
            w.wedges.push_back(d);
        }
        wheels.push_back(w);
    }
    int cnt=0;
    bool res = false;
    for(int i=0;!res&&i<360;++i)
    {
        for(int ang=0;!res&&ang<360;++ang)
        {
            cnt=0;
            for(int j=0;j<5;++j)
            {
                if(wheels[j].pass(i,ang))cnt++;
            }
            if(cnt==5)
            {
                res = true;
                fout << i << endl;
            }
        }
    }
    if(!res) fout << "none" << endl;
    fin.close();
    fout.close();
    return 0;
}

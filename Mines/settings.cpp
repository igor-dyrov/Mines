#include "settings.h"



bool operator == (const Cell & one, const Cell & other)
{
    if ((one.x == other.x)&&(one.y==other.y)) return true;
    return false;
}

bool operator != (const Cell & one, const Cell & other)
{
    if ((one.x == other.x)&&(one.y==other.y)) return false;
    return true;
}
bool operator <= (const Cell & one, const Cell & other)
{
    if (sqrt(one.x*one.x+one.y*one.y)<=sqrt(other.x*other.x+other.y*other.y)) return true;
    return true;
}

bool operator >= (const Cell & one, const Cell & other)
{
    if (sqrt(one.x*one.x+one.y*one.y)<=sqrt(other.x*other.x+other.y*other.y)) return true;
    return false;
}
bool operator < (const Cell & one, const Cell & other)
{
    if (sqrt(one.x*one.x+one.y*one.y)<sqrt(other.x*other.x+other.y*other.y)) return true;
    return true;
}

bool operator > (const Cell & one, const Cell & other)
{
    if (sqrt(one.x*one.x+one.y*one.y)<sqrt(other.x*other.x+other.y*other.y)) return true;
    return false;
}

void Cell::SetVar(float _var)
{
    var = _var;
}

float Cell::GetVar()
{
    return var;
}

ostream& operator << (ostream & os,const Cell& obj)
{
    os << obj.x << " " << obj.y << " " << obj.var << " ";
    return os;
}


ostream& operator << (ostream & os,const Group& obj)
{
    for (auto itr : obj.cells) os << itr.get() << " \n";
    os << '\n' << "--------------------------" << '\n';
    return os;
}

void FillVar(vector<Group> &Groups)
{
    for (auto &grp : Groups)
    {
        for (auto &itr : grp.cells)
        {
            if (itr.get().GetVar() != -1.0)
            {
                float cff = 1-itr.get().GetVar();
                if((cff < 0.0) || (cff > 1.0))
                {
                    cout << "\n Bad field \n";
                    return;
                }
                itr.get().SetVar(1 - (1- (float)grp.mines_around / (float)grp.cells.size())*cff);
            }
            else
            {
                itr.get().SetVar((float)grp.mines_around / (float)grp.cells.size());
            }
        }
    }
  bool repeat = true;
    while (repeat)
    {
        repeat = false;
        for (auto &grp : Groups)
        {
            float sum = 0.0;
            for (auto &itr : grp.cells) sum+=itr.get().GetVar();
            if (abs(sum-(float)grp.mines_around)>1.0)
            {
                cout << "\n Bad field \n";
                return;
            }
            if(abs(sum-(float)grp.mines_around)>0.01)
            {
                repeat = true;
                ReCount(grp.cells,(float)grp.mines_around/sum);
            }

        }
    }
    for (auto &grp : Groups)
    {
        for (auto &itr : grp.cells)
        {
            if (itr.get().GetVar() > 0.99) itr.get().SetVar(0.99);
            else if (itr.get().GetVar() < 0) itr.get().SetVar(0);
        }
    }
}


void ReCount(vector<std::reference_wrapper<Cell>> & ToCorrect, float Cff)
{
    for (auto &itr : ToCorrect)
    {
        itr.get().SetVar(Cff*itr.get().GetVar());
    }
}



bool Neighbor(int x1, int y1, int x2, int y2)
{
    if ((abs(x1 - x2) < 2) && (abs(y1 - y2) < 2)) return true;
    else return false;
}

Group::Group(const vector<std::reference_wrapper<Cell>> &_set, int mines)
{
    for (auto i : _set) cells.push_back(i);
    for (auto i : cells) i.get().SetVar(-1.0);
    mines_around = mines;
}



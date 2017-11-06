#include "settings.h"

template<class Iter>

void binary_sort(Iter beg, Iter _end)
{
    if (beg<_end)
    {
        Iter temp = beg;
        int size=1;
        while(temp != _end)
        {
            size++;
            temp++;
        }
        if (*beg == *_end) return;
        Cell mid = *(beg+size/2);
        Iter left = beg, right = _end;
        while(left <= right)
        {
            while(*left<mid) left++;
            while(*right>mid) right--;
            if(left<=right)
            {
                iter_swap(left,right);
                left++; right--;
            }
        }
        binary_sort(beg,right);
        binary_sort(left,_end);
    }
}


int Group::Cardinality()
{
    return (int)cells.size();
}

Group::Group(const vector<std::reference_wrapper<Cell>> &_set, int mines)
{
    for (auto i : _set) cells.push_back(i);
    mines_around = mines;
}

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

void Cell::Correct(float NextVar)
{
    var = 1 - (1*var)*(1-NextVar);
}

ostream& operator << (ostream & os,const Cell& obj)
{
    os << obj.x << " " << obj.y << " " << obj.var;
    return os;
}

void Group::SetToZero()
{
    cells.clear();
    mines_around =0;
}

bool Owns(const vector<Cell> &_set1, const vector<Cell> &_set2)
{
    for(const auto  &itr :_set2)
    {
        for (const auto  &fnd :_set1)
        {
            if (itr == fnd) break;
        }
        return false;
    }
    return true;
}

vector<Cell> GroupIntersection(const vector<Cell> &_set1, const vector<Cell> &_set2)
{
    vector<Cell> Intersection;
    for(const auto  &itr :_set2)
    {
        for (const auto  &fnd :_set1)
        {
            if (itr == fnd) Intersection.push_back(itr);
        }
    }
    return Intersection;
}

void SubCells(vector<Cell> &parent, vector<Cell> &child)
{
   vector<vector<Cell>::iterator> ToErase;
    for (auto itr: child)
    {
        for (auto fnd = parent.begin();fnd != parent.end();fnd++)
        {
            if (*fnd == itr)
            {
                ToErase.push_back(fnd);
            }
        }
    }
    for (auto tmp:ToErase) parent.erase(tmp);
    //cout << parent.size();
}


/*void GroupOperate(vector<Group> & AllGroups)
{
    for (auto i =AllGroups.begin();i!=AllGroups.end();i++)
    {
        for(auto j =i+1;j!=AllGroups.end();j++)
        {
            Group &G1 = *i, &G2 = *j;
           if (G1.cells == G2.cells) G2.SetToZero();
            else if (Owns(G1.cells, G2.cells))
            {
                for (auto itr = G2.cells.begin(); itr != G2.cells.end(); itr++)
                {
                    G1.cells.erase(itr);
                }
                G1.mines_around -= G2.mines_around;
            }
            else {
                vector<Cell> Intersection = GroupIntersection(G1.cells, G2.cells);
                if (Intersection.size())
                {
                    Group New(Intersection,0);
                    if (G1.mines_around >= G2.mines_around)
                    {
                        SubCells(G1.cells,Intersection);
                        SubCells(G2.cells,Intersection);
                        New.mines_around = G1.mines_around - G2.cells.size();
                        G1.mines_around -= New.mines_around;
                        G2.mines_around -= New.mines_around;
                        AllGroups.push_back(New);
                        if (New.mines_around != G2.cells.size()) break;
                    }
                    else
                    {
                        SubCells(G1.cells,Intersection);
                        SubCells(G2.cells,Intersection);
                        New.mines_around = G2.mines_around - G1.cells.size();
                        G1.mines_around -= New.mines_around;
                        G2.mines_around -= New.mines_around;
                        AllGroups.push_back(New);
                        if (New.mines_around != G1.cells.size()) return;
                    }
                }
            }
        }
    }
}*/

ostream& operator << (ostream & os,const Group& obj)
{
    for (auto itr : obj.cells) os << itr.get() << " \n";
    os<< obj.mines_around << '\n';
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
				itr.get().SetVar(1 - (1 - (float)grp.mines_around / (float)grp.cells.size())*(1 - itr.get().GetVar()));
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
            cout << sum << '\n';
            sleep(1);
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

float Contains(const vector<Cell> &Cells, const Cell& Elem)
{
    for (auto itr : Cells)
    {
        if(Elem == itr) return itr.GetVar();
    }
    return -1.0;
}

#include <iostream>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <zconf.h>

using namespace std;

struct point //cell with number of mines around
{
    size_t x,y;
    int num_of_mines;
};

class Cell //unit for being processed
{
private:
    int x,y;
    float var;
public:
    Cell(){}
    Cell(int _x,int _y): x(_x),y(_y){}
    friend bool operator != (const Cell & one,const Cell & other);
    friend bool operator == (const Cell & one,const Cell & other);
    friend bool operator < (const Cell & one,const Cell & other);
    friend bool operator > (const Cell & one,const Cell & other);
    friend bool operator <= (const Cell & one,const Cell & other);
    friend bool operator >= (const Cell & one,const Cell & other);
    friend ostream& operator << (ostream &,const Cell&);
    void Correct(float);
    friend void ReCount(vector<std::reference_wrapper<Cell>> &, float);
    void SetVar(float _var);
    float GetVar();
};

class Group {
private:
    vector<std::reference_wrapper<Cell>> cells;
    int mines_around;
public:
    Group(const vector<std::reference_wrapper<Cell>> &_set, int);
    int Cardinality();
    friend void GroupOperate(vector<Group> &);
    friend void FillVar(vector<Group>&);
    friend ostream& operator << (ostream &,const Group&);
    void SetToZero();
};

bool Owns(const vector<std::reference_wrapper<Cell>> &, const vector<std::reference_wrapper<Cell>> &);
vector<Cell> GroupIntersection(const vector<std::reference_wrapper<Cell>> &, const vector<std::reference_wrapper<Cell>> &);
void SubCells(vector<std::reference_wrapper<Cell>> &,vector<Cell>&);
void ReCount(Group &, float);
float Contains(const vector<Cell>&, const Cell&);
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct point //cell with number of mines around
{
    point(int _x,int _y,int num){x =_x;y = _y,num_of_mines = num;}
    int x,y;
    int num_of_mines;
};

class Cell //unit for being processed
{
private:
    int x,y;
    float var;
public:
    Cell(){}
    Cell(int _x,int _y): x(_x),y(_y){var =0;}
    friend bool operator != (const Cell & one,const Cell & other);
    friend bool operator == (const Cell & one,const Cell & other);
    friend bool operator < (const Cell & one,const Cell & other);
    friend bool operator > (const Cell & one,const Cell & other);
    friend bool operator <= (const Cell & one,const Cell & other);
    friend bool operator >= (const Cell & one,const Cell & other);
    friend ostream& operator << (ostream &,const Cell&);
    int X(){return x;}
    int Y(){return y;}
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
    friend void FillVar(vector<Group>&);
    friend ostream& operator << (ostream &,const Group&);
};

struct AllIn
{
    vector<point> Points;
    vector<Cell> Cells;
    vector<pair<int,int>> Mines;
};

bool Neighbor(int x1, int y1, int x2, int y2);

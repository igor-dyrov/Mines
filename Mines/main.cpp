#include "settings.h"

AllIn Prepare(char *StartPath)
{
    ifstream fr(StartPath);
    int wid, hei;
    char temp;
    AllIn Result;
    fr >> wid; fr >> hei;
    for (int i=0;i<hei;i++)
    {
        for (int j =0;j<wid;j++)
        {
            fr >> temp;
            if (temp == '?')
            {
                Result.Cells.push_back(Cell(i,j));
            }
            else if(((int)temp >= 49) && ((int)temp <= 56))
            {
                Result.Points.push_back(point(i,j,((int)temp-48)));
            }
            else if (temp == '!') Result.Mines.push_back(make_pair(i,j));
        }
    }
    fr.close();
    return Result;
}

void Match(vector<point> &Help, vector<pair<int,int>> &Mines)
{
    for (auto &i : Help)
    {
        for (auto j : Mines)
        {
            if (Neighbor(i.x,i.y,j.first,j.second)) i.num_of_mines -= 1;
        }
    }
}

void WriteAns(char *ExtPath,const vector<Cell> &Result)
{
    ofstream wr(ExtPath);
    for (auto i : Result)
    {
        wr << i << '\n';
    }
    wr.close();
}

bool CheckParam(char *f1, char*f2, char*f3)
{
    ifstream F1(f1);
    ifstream F2(f2);
    ifstream F3(f3);
    if ((!F1.is_open()) || (!F2.is_open()) || (!F3.is_open()))
    {
        cout << "\n Check Args! \n";
        return false;
    }
    F1.close();
    F2.close();
    F3.close();
    return true;
}

bool Test(char* F1, char *F2)
{
    ifstream f1(F1);
    ifstream f2(F2);
    int x1, y1, x2,y2;
    float var1, var2;
    while(!f1.eof())
    {
        f1 >> x1 >> y1 >> var1;
        f2 >> x2 >> y2 >> var2;
        if ((x1 != x2) || (y1 != y2) || (abs(var1 - var2) >0.01)) return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (CheckParam(argv[1],argv[2],argv[3])) {
        AllIn Start = Prepare(argv[1]);
        Match(Start.Points, Start.Mines);
        vector<Group> Result;
        vector<vector<reference_wrapper<Cell>>> Storage;
        for (auto i: Start.Points) {
            Storage.push_back(vector<reference_wrapper<Cell>>());
            for (auto &j:Start.Cells) {
                if (Neighbor(i.x, i.y, j.X(), j.Y())) (Storage.end()-1)->push_back(ref(j));
            }
            Result.push_back(Group(*(Storage.end()-1), i.num_of_mines));
        }
        FillVar(Result);
        for (auto &i : Start.Cells) {
            i.SetVar(round(i.GetVar() * 100) / 100);
        }
        WriteAns(argv[2], Start.Cells);
        if(Test (argv[2], argv[3])) cout << "\n Correct! \n";
        else cout << "\n Incorrect! \n";
    }
    return 0;
}





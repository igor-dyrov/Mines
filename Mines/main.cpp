#include "settings.h"

int main()
{
    /*Cell q(0,0), w(0,1), e(0,2), r(1,0), t(1,2), y(2,0), u(2,2),i(3,0),o(3,1),p(3,2);
    vector<std::reference_wrapper<Cell>> cells;
    cells.push_back(ref(q)); cells.push_back(ref(w)); cells.push_back(ref(e)); cells.push_back(ref(r)); cells.push_back(ref(t));
    cells.push_back(ref(y)); cells.push_back(ref(u));
    Group g1(cells,4);
    vector<std::reference_wrapper<Cell>> cells1;
    cells1.push_back(ref(r)); cells1.push_back(ref(t)); cells1.push_back(ref(y)); cells1.push_back(ref(u));
    cells1.push_back(ref(i)); cells1.push_back(ref(o)); cells1.push_back(ref(p));
    Group g2(cells1,2);
    vector<Group> groups;
    groups.push_back(g1); groups.push_back(g2);*/
    vector<Group> groups;
    Cell q(0,1), w(1,0), e(1,1), r(2,0), t(2,1), y(3,1);
    vector<std::reference_wrapper<Cell>> cells;
    cells.push_back(ref(q)); cells.push_back(ref(w)); cells.push_back(ref(e));
    vector<std::reference_wrapper<Cell>> cells1;
    cells1.push_back(ref(r)); cells1.push_back(ref(t)); cells1.push_back(ref(y));
    Group g1(cells,3), g2(cells1,3);
    groups.push_back(g1); groups.push_back(g2);
    FillVar(groups);
    for (auto i:groups) cout << i;
    return 0;
}
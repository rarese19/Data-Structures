#include <iostream>
#include <fstream>
#include <deque>
#include <cstdlib>

using namespace std;

typedef struct solarian {
    int index;
    int varsta;
}*sol;

sol newS(int index, int varsta){
    sol s = new solarian();
    s->index = index;
    s->varsta = varsta;

    return s;
}

ifstream f("vila2.in");
ofstream g("vila2.out");

int main() {
    int n, k, v, vm = 0;
    f>>n>>k;
    deque<sol> dmin, dmax;

    for (int i=1; i<=n; i++){
        f>>v;
        sol a = newS(i, v);

        if (!dmin.empty() && (a->index - dmin.front()->index) > k)
            dmin.pop_front();

        while (!dmin.empty() && (a->varsta < dmin.back()->varsta))
            dmin.pop_back();
        dmin.push_back(a);

        if (!dmax.empty() && (a->index - dmax.front()->index) > k)
            dmax.pop_front();

        while (!dmax.empty() && (a->varsta > dmax.back()->varsta))
            dmax.pop_back();
        dmax.push_back(a);

        if (i >= k){
            if (dmax.front()->varsta - dmin.front()->varsta > vm)
                vm = dmax.front()->varsta - dmin.front()->varsta;
        }

    }

    g<<vm;
    return 0;
}
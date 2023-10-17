#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

typedef struct saptamana {
    int numar;
    long long c;
    long long p;
}*sap;

sap news(int numar, long long cost, long long productie){
    sap s = new saptamana();
    s->numar = numar;
    s->c = cost;
    s->p = productie;
    return s;
}

ifstream f("branza.in");
ofstream g("branza.out");

int main() {
    int n, s, t;
    f>>n>>s>>t;
    long long sum = 0, cost, productie;

    deque<sap> de;

    for (int i=0; i<n; i++){
        f>>cost>>productie;
        sap a = news(i, cost, productie);

        if (!de.empty() && de.front()->numar < i - t)
            de.pop_front();

        while (!de.empty() && (s * (i - de.back()->numar) + de.back()->c) >= cost)
            de.pop_back();

        de.push_back(a);

        sum += (s * productie * (i - de.front()->numar) + productie * de.front()->c);
    }
    de.clear();

    g<<sum;

    return 0;
}
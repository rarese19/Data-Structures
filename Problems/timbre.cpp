#include <bits/stdc++.h>

using namespace std;
ifstream f("timbre.in");
ofstream g("timbre.out");

int main(){
    int n, m, k, mi, c;
    f>>n>>m>>k;
    vector<pair<int, int>> intervale;
    multiset<int> timbre;

    for (int i=0; i<m; i++){
        f>>mi>>c;
        intervale.push_back(make_pair(mi, c));
    }
    sort(intervale.begin(), intervale.end(), [](pair<int, int> a, pair<int, int> b){
        return a.first < b.first;
    });

    for (int i=0; i<intervale.size(); i++)
        cout<<intervale[i].first<<" "<<intervale[i].second<<endl;

    int suma = 0;
    m--;
    while (n >0){
        while (m>= 0 and intervale[m].first > n){
            timbre.insert(intervale[m].second);
            m--;
        }
        n -= k;
        suma += *timbre.begin();
        timbre.erase(timbre.begin());
    }

    g<<suma<<endl;
    return 0;
}
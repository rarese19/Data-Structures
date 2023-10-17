#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;
ifstream f("muzica.in");
ofstream g("muzica.out");

int main(){
    long n, m, cnt = 0;
    long s = 0, mel, a, b, c, d, e;
    f>>n>>m;
    f>>a>>b>>c>>d>>e;

    unordered_set<long long> v;
    for (int i=0; i<n; i++) {
        f>>mel;
        v.insert(mel);
    }

    for (int i=2; i<m; i++){
        if (s == 0){
            if (v.find(a) != v.end()){
                ++cnt;
                v.erase(a);
            }

            if (v.find(b) != v.end()){
                ++cnt;
                v.erase(b);
            }
        }

        s = (c * b + d * a) % e;

        if (v.find(s) != v.end()){
            ++cnt;
            v.erase(s);
        }

        a = b;
        b = s;
    }

    g<<cnt;

    f.close();
    g.close();
    return 0;
}
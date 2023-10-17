#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;
ifstream f("pariuri.in");
ofstream g("pariuri.out");

int main() {
    int n, m, bani, timp;
    f>>n;
    unordered_map<int, int> lista;
    for (int i=0; i<n; i++){
        f>>m;
        for (int j=0; j<m; j++){
            f>>timp>>bani;
            lista[timp] += bani;
        }
    }
    g<<lista.size()<<endl;
    for (auto sol: lista){
        g<<sol.first<<" "<<sol.second<<" ";
    }
    return 0;
}
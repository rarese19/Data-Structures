#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;
ifstream f("loto.in");
ofstream g("loto.out");

int main() {
    int n, s;
    f>>n>>s;
    int a[101];
    unordered_map<int, vector<int>> m;
    priority_queue<int, vector<int>, greater<int>> p;
    for (int i=0; i<n; i++)
        f>>a[i];

    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            for (int k=0; k<n; k++){
                if (m.find(a[i] + a[j] + a[k]) == m.end()) {
                    m[a[i] + a[j] + a[k]].push_back(a[i]);
                    m[a[i] + a[j] + a[k]].push_back(a[j]);
                    m[a[i] + a[j] + a[k]].push_back(a[k]);
                }
            }

    int r = 0;
    for (int i=0; i<n && r==0; i++)
        for (int j=0; j<n && r==0; j++)
            for (int k=0; k<n && r==0; k++){
                if (m.find(s - (a[i] + a[j] + a[k])) != m.end()){
                    r = 1;
                    for (int l=0; l<m.find(s - (a[i] + a[j] + a[k]))->second.size(); l++){
                        p.push(m.find(s - (a[i] + a[j] + a[k]))->second[l]);
                    }
                    p.push(a[i]);
                    p.push(a[j]);
                    p.push(a[k]);
                }
            }

    if (p.empty()) {
        g << -1;
    }

    while (!p.empty()){
        int temp = p.top();
        p.pop();
        g<<temp<<" ";
    }
    return 0;
}
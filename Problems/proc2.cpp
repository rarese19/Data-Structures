#include <bits/stdc++.h>

using namespace std;
ifstream f("proc2.in");
ofstream g("proc2.out");

int main(){
    int n, m, s, d;
    f>>n>>m;

    priority_queue<int, vector<int>, greater<int>> free;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> busy;

    for (int i=1; i<=n; i++)
        free.push(i);

    for (int i=0; i<m; i++){
        f>>s>>d;
        while (!busy.empty() && busy.top().first <= s){
            free.push(busy.top().second);
            busy.pop();
        }
        
        int x = free.top();
        free.pop();
        g<<x<<'\n';
        busy.push({s+d, x});
    }
    
    return 0;
}
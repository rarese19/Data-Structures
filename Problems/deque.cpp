#include <iostream>
#include <fstream>

using namespace std;

ifstream f("deque.in");
ofstream g("deque.out");
int a[5000005], deq[5000005];
long long sum = 0;
int fr = 1, b = 0;

int main(){
    int n, k;
    f>>n>>k;


    for (int i=1; i<=n; i++)
        f>>a[i];

    for (int i=1; i<=n; i++){
        if(fr <= b && deq[fr] == i - k)
            ++fr;

        while (fr <= b && a[i] <= a[deq[b]])
            --b;

        deq[++b] = i;

        if (i >= k)
            sum += a[deq[fr]];
    }

    g<<sum;
    return 0;
}
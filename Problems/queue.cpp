#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

ifstream f("queue.in");
ofstream g("queue.out");
stack<int> s1, s2;


int main() {
    string in;
    int wr, n;
    f>>n;
    f.get();

    for (int i=0; i<n; i++){
        wr = 0;
        getline(f, in);
        if (in[4] == '_') {
            int q = 10;
            int pow = 10;
            while (in[q] != ')'){
                wr = wr * pow + (in[q] - '0');
                q++;
            }

            s1.push(wr);
            g<<i+1<<": read("<<wr<<") push(1,"<<wr<<")\n";
        } else if (in[3] == '_') {
            if (s2.empty()) {
                if (s1.size() > 1)
                    g<<i+1<<": ";
                while (s1.size() > 1) {
                    wr = s1.top();
                    s1.pop();
                    s2.push(wr);
                    g << "pop(1) push(2," << wr << ") ";
                }
                wr = s1.top();
                s1.pop();
                g<<"pop(1) write("<<wr<<")\n";
            }
            else {
                wr = s2.top();
                s2.pop();
                g<<i+1<<": pop(2) write("<<wr<<")\n";
            }
        }
    }

    return 0;
}
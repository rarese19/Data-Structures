#include <iostream>
#include <fstream>
#include <deque>
#include <string>

using namespace std;

ifstream f("alibaba.in");
ofstream g("alibaba.out");

int main(){
    deque<char> de;
    int n, k;
    string numar;
    f>>n>>k>>numar;

    string rezultat = "";

    for (int i=0; i<numar.length(); i++){
        while (!de.empty() && k != 0 && numar[i] > de.back()){
            --k;
            de.pop_back();
        }
        de.push_back(numar[i]);
    }

    if (k != 0)
        for (int i=0; i<de.size() - k; i++)
            g<<de[i];
    else for (int i=0; i<de.size(); i++)
        g<<de[i];


    return 0;
}
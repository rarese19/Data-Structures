#include <iostream>
#include <vector>


using namespace std;

int main() {
    int n;
    vector<int> rooms;
    cin>>n;
    for (int i=0; i<10; i++){
        rooms.push_back(0);
    }
    char a;
    for (int i=0; i<n; i++){
        cin>>a;

        if (a == 'L')
            for (int i=0; i<10; i++)
                if (rooms[i] == 0){
                    rooms[i] = 1;
                    break;
                }

        if (a == 'R')
            for (int i=9; i>=0; i--)
                if (rooms[i] == 0){
                    rooms[i] = 1;
                    break;
                }

        if (a != 'L' && a != 'R'){
            rooms[a - '0'] = 0;
        }
    }

    for (int i=0; i<10; i++){
        cout<<rooms[i];
    }


    return 0;
}
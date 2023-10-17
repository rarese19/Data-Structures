#include <bits/stdc++.h>

using namespace std;
ifstream f("hashuri.in");
ofstream g("hashuri.out");


typedef struct Nod {
    int value;
    struct Nod* next;
}*PNod;

Nod* newN(int value) {
    PNod nou = new Nod();
    nou->value = value;
    nou->next = NULL;

    return nou;
};

class Hash {
    PNod *arr;

    int hash(int value){
        return value % 666013;
    }
public:
    Hash(){
        this->arr = new PNod[666013];
    }

    void insertElement(int value){
        PNod a = newN(value);

        if (arr[hash(value)] == nullptr){
            arr[hash(value)] = a;
        }
        else {
            PNod parcurgere = arr[hash(value)];

            while (parcurgere->next != nullptr)
                parcurgere = parcurgere->next;

            parcurgere->next = a;
        }
    }

    void deleteElement(int value){
        if (arr[hash(value)] == nullptr)
            return;

        PNod parcurgere = arr[hash(value)];

        if (parcurgere->value == value){
            arr[hash(value)] = parcurgere->next;
            parcurgere->next = NULL;
            delete parcurgere;

            return;
        }

        PNod predecesor;

        while (parcurgere != nullptr){
            if (parcurgere->value == value){
                predecesor->next = parcurgere->next;
                parcurgere->next = nullptr;
                delete parcurgere;

                return;
            }

            predecesor = parcurgere;

            parcurgere = parcurgere->next;
        }
    }

    int searchElement(int value){
        if (arr[hash(value)] == nullptr)
            return 0;

        PNod parcurgere = arr[hash(value)];

        while (parcurgere != nullptr){
            if (parcurgere->value == value)
                return 1;

            parcurgere = parcurgere->next;
        }

        return 0;
    }

    ~Hash(){
        delete this->arr;
    }
};

int main() {
    Hash a;
    int n, operatie, valoare;
    f>>n;

    for (int i=0; i<n; i++){
        f>>operatie;

        if (operatie == 1){
            f>>valoare;
            a.insertElement(valoare);
        }

        if (operatie == 2){
            f>>valoare;
            a.deleteElement(valoare);
        }

        if (operatie == 3){
            f>>valoare;
            g<<a.searchElement(valoare)<<endl;
        }
    }

    f.close();
    g.close();
    return 0;
}
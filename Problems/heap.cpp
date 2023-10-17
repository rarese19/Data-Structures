//Nu este corecta, nu are 100p.
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream f("heapuri.in");
ofstream g("heapuri.out");

typedef struct Nod {
    int valoare;
    int cron;
}Nod;

class minHeap {
    Nod* arr;
    int cnt;

    int nrElemente;

    int parent(int index){
        return arr[(index - 1) / 2].valoare;
    }

    int leftChild(int index){
        return index * 2;
    }

    int rightChild(int index){
        return index * 2 + 1;
    }

public:
    minHeap(){
        this->arr = new Nod[200005];
        this->nrElemente = 0;
        cnt = 0;
    }

    void insertElement(int value){
        ++nrElemente;
        ++cnt;

        arr[nrElemente].valoare = value;
        arr[nrElemente].cron = cnt;

        int aux = nrElemente;

        while (aux / 2 > 0 && arr[aux].valoare < arr[aux / 2].valoare) {
            swap(arr[aux], arr[aux  / 2]);
            aux = aux  / 2;
        }
    }

    void deleteElement(int ins){
        int i;
        for (i=1; i<=nrElemente; i++)
            if (arr[i].cron == ins){
                break;
            }

        swap(arr[i], arr[nrElemente]);
        arr[nrElemente].valoare = 0;
        arr[nrElemente].cron = 0;
        --nrElemente;

        if (i >= nrElemente)
            return;

        int lchild = leftChild(i), current = i;

        while (lchild <= nrElemente){
            int pos = lchild, rchild = lchild + 1;

            if (rchild <= nrElemente && arr[lchild].valoare > arr[rchild].valoare)
                pos = rchild;

            if (arr[current].valoare < arr[pos].valoare)
                break;
            else {
                swap(arr[current], arr[pos]);
                current = i;
                lchild = leftChild(current);
            }
        }
    }

    int showMin(){
       return this->arr[1].valoare;
    }
};

int main() {
    minHeap a;
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
            g<<a.showMin()<<endl;
        }
    }

    return 0;
}
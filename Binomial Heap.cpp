#include <iostream>
#include <vector>
#include <fstream>
#include <vector>

using namespace std;

typedef struct Nod {
    long long int key;
    long long int chldnumber;
    struct Nod* child;
    struct Nod* parent;
    struct Nod* brother;

} Nod, *PNod;

PNod createnod(long long int key) {
    PNod newNode = new Nod;
    newNode->key = key;
    newNode->chldnumber = 0;
    newNode->child = NULL;
    newNode->parent = NULL;
    newNode->brother = NULL;

    return newNode;
}

class BinHeap {
    PNod root;

    void mergeTrees(PNod root1, PNod root2){
        if (root1->key > root2->key){
            root1->brother = root2->brother;
            root2->brother = root1->child;
            root1->child = root2;
            root2->parent = root1;
            root1->chldnumber ++;
        }
        else {
            root1->brother = root2->child;
            root2->child = root1;
            root1->parent = root2;
            root2->chldnumber ++;

        }
        if (this->root == root1 || this->root == root2){
            if (root1->parent == NULL)
                this->root = root1;
            if (root2->parent == NULL)
                this->root = root2;
        }
    }

    PNod deleteRoot(PNod root){

        PNod new_root = NULL;
        PNod succesor = NULL;
        PNod parcurgere = root->child;
        PNod predecesor = NULL;

        while (parcurgere != NULL){
            parcurgere->parent = NULL;

            succesor = parcurgere->brother;
            parcurgere->brother = predecesor;
            predecesor = parcurgere;
            parcurgere = succesor;
        }

        new_root = predecesor;
        return new_root;
    }

    void fix() {
        PNod parametru = NULL;
        PNod parcurgere = this->root;
        PNod predecesor = NULL;
        PNod succesor = NULL;

        if (this->root == NULL || this->root->brother == NULL)
            return;

        if (parcurgere->brother->brother == NULL){
            succesor = parcurgere->brother;
            if (parcurgere->chldnumber == succesor->chldnumber){
                mergeTrees(parcurgere, succesor);
            }
            return;
        }

        predecesor = parcurgere;
        parcurgere = parcurgere->brother;
        succesor = parcurgere->brother;
        parametru = NULL;

        while (predecesor != NULL){
            if (parcurgere == NULL)
                predecesor = NULL;
            else if (predecesor->chldnumber < parcurgere->chldnumber){
                if (succesor != NULL)
                    succesor = succesor->brother;
                parcurgere = parcurgere->brother;
                parametru = predecesor;
                predecesor = predecesor->brother;
            }
            else if (succesor != NULL && predecesor->chldnumber == parcurgere->chldnumber && predecesor->chldnumber == succesor->chldnumber){
                succesor = succesor->brother;
                parcurgere = parcurgere->brother;
                parametru = predecesor;
                predecesor = predecesor->brother;
            }
            else if (predecesor->chldnumber == parcurgere->chldnumber){
                if (parcurgere->key >= predecesor->key){
                    if (parametru != NULL)
                        parametru->brother = parcurgere;
                    mergeTrees(predecesor, parcurgere);
                    predecesor = parcurgere;
                }
                else mergeTrees(predecesor, parcurgere);

                parcurgere = succesor;
                if (succesor != NULL && succesor->brother != NULL)
                    succesor = succesor->brother;

                if (parcurgere == NULL)
                    return;

                if (parcurgere == succesor){
                    if (predecesor->chldnumber == parcurgere->chldnumber) {
                        if (parcurgere->key >= predecesor->key)
                            if (parametru != NULL)
                                parametru->brother = parcurgere;
                        mergeTrees(predecesor, parcurgere);
                    }
                    return;
                }
            }
        }
    }

public:
    BinHeap();

    void insertElement(long long int key){
        PNod element = createnod(key);
        element->key = key;

        if (this->root == NULL){
            this->root = element;
            return;
        }

        element->brother = this->root;
        this->root = element;

        fix();
    }

    PNod findMax() {
        if (this->root == NULL)
            return NULL;

        PNod m = this->root;
        PNod parcurgere = this->root->brother;

        while (parcurgere != NULL){
            if (parcurgere->key > m->key)
                m = parcurgere;
            parcurgere = parcurgere->brother;
        }

        return m;
    }

    void deleteMax() {
        if (this->root == NULL)
            return;

        PNod m = this->findMax();

        PNod parcurgere = this->root;
        PNod predecesor = NULL;
        while (parcurgere->key != m->key){
            predecesor = parcurgere;
            parcurgere = parcurgere->brother;
        }

        if (m == this->root && this->root->brother == NULL){
            this->root = deleteRoot(m);
            return;
        }

        PNod newRoot = deleteRoot(m);

        if (m->brother != NULL)
            if (this->root == m)
                this->root = m->brother;
            else predecesor->brother = m->brother;
        else if (predecesor != NULL)
            predecesor->brother = NULL;


        BinHeap newHeap;
        newHeap.root = newRoot;

        this->heapUnion(newHeap);
    }

    void heapUnion(BinHeap heap1) {
        PNod new_heap = NULL;
        PNod parcurgereHeap = NULL;
        PNod last = NULL;
        PNod parcurgere1 = this->root;
        PNod parcurgere2 = heap1.root;

        while (parcurgere1 != NULL && parcurgere2 != NULL){
            parcurgereHeap = new_heap;
            last = NULL;
            while (parcurgereHeap != NULL){
                last = parcurgereHeap;
                parcurgereHeap = parcurgereHeap->brother;
            }

            if (parcurgere1->chldnumber <= parcurgere2->chldnumber){
                if (new_heap == NULL){
                    new_heap = parcurgere1;
                    parcurgere1 = parcurgere1->brother;
                    new_heap->brother = NULL;
                }
                else {
                    last->brother = parcurgere1;
                    parcurgere1 = parcurgere1->brother;
                    if (last!= NULL)
                        last->brother->brother = NULL;

                }
            }
            else {
                if (new_heap == NULL){
                    new_heap = parcurgere2;
                    parcurgere2 = parcurgere2->brother;
                    new_heap->brother = NULL;
                }
                else {
                    last->brother = parcurgere2;
                    parcurgere2 = parcurgere2->brother;
                    if (last != NULL)
                        last->brother->brother = NULL;
                }

            }
        }

        parcurgereHeap = new_heap;
        last = NULL;
        while (parcurgereHeap != NULL){
            last = parcurgereHeap;
            parcurgereHeap = parcurgereHeap->brother;
        }

        while (parcurgere1 != NULL){
            if (last == NULL) {
                new_heap = parcurgere1;
                break;
            }
            last->brother = parcurgere1;
            parcurgere1 = parcurgere1->brother;
            last = last->brother;
        }

        while (parcurgere2 != NULL){
            if (last == NULL) {
                new_heap = parcurgere2;
                break;
            }
            last->brother = parcurgere2;
            parcurgere2 = parcurgere2->brother;
            last = last->brother;
        }

        this->root = new_heap;

        fix();

    }
};

BinHeap::BinHeap() {
    this->root = NULL;
}



int main(){
    vector<BinHeap*> heapuri;

    ifstream f("mergeheap.in");
    ofstream g("mergeheap.out");

    int numar_heap;
    long long int numar_operatii;
    int operatie;
    int multime1, multime2;
    int element;

    f>>numar_heap>>numar_operatii;

    for (int i=0; i<numar_heap; i++){
        BinHeap* n = new BinHeap();
        heapuri.push_back(n);
    }

    for (int i=0; i<numar_operatii; i++){
        f>>operatie;
        if (operatie == 1){
            f>>multime1;
            f>>element;
            heapuri[multime1 - 1]->insertElement(element);
        }

        if (operatie == 2){
            f>>multime1;
            PNod m = heapuri[multime1 - 1]->findMax();
            g<<m->key<<endl;
            heapuri[multime1 - 1]->deleteMax();
        }

        if (operatie == 3){
            f>>multime1;
            f>>multime2;

            heapuri[multime1 - 1]->heapUnion(*heapuri[multime2 - 1]);

            BinHeap* a = new BinHeap();
            heapuri[multime2 - 1] = a;
        }
    }

    return 0;
}
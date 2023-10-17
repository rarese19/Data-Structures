#include <iostream>
#include <fstream>

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Nod {
    struct Nod* parent;
    struct Nod* leftChild;
    struct Nod* rightChild;
    long long int balanceFactor;
    long long int height;
    long long int key;
    long long int value;
} Nod, *PNod;

PNod createNod(long long int key, long long int value){
    PNod newNode = new Nod;
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->balanceFactor = 0;
    newNode->height = 0;
    newNode->key = key;
    newNode->value = value;

    return newNode;
}

class AVL{
    int size;
    PNod root;

    void nodeHeight(PNod nod){
        if (nod == NULL)
            return;

        int left = -1, right = -1;

        if (nod->rightChild)
            right = nod->rightChild->height;
        if (nod->leftChild)
            left = nod->leftChild->height;

        nod->height = MAX(left, right) + 1;
        nod->balanceFactor = right - left;
    }

    void rotateRight(PNod nod){
        if (nod == NULL || nod->parent == NULL)
            return;

        PNod parent = nod->parent;
        PNod grandParent = nod->parent->parent;

        parent->leftChild = nod->rightChild;
        if (parent->leftChild != NULL)
            parent->leftChild->parent = parent;

        nod->rightChild = parent;
        parent->parent = nod;

        if (grandParent == NULL) {
            root = nod;
            nod->parent = NULL;
        }
        else {
            nod->parent = grandParent;
            if (grandParent->key > nod->key)
                grandParent->leftChild = nod;
            else grandParent->rightChild = nod;
        }

        nodeHeight(parent);
        nodeHeight(parent->parent);
    }

    void rotateLeft(PNod nod){
        if (nod == NULL || nod->parent == NULL)
            return;

        PNod parent = nod->parent;
        PNod grandParent = nod->parent->parent;

        parent->rightChild = nod->leftChild;
        if (parent->rightChild != NULL)
            parent->rightChild->parent = parent;

        nod->leftChild = parent;
        parent->parent = nod;
        if (grandParent == NULL){
            root = nod;
            nod->parent = NULL;
        }
        else {
            nod->parent = grandParent;
            if (grandParent->key > nod->key)
                grandParent->leftChild = nod;
            else grandParent->rightChild = nod;
        }

        nodeHeight(parent);
        nodeHeight(parent->parent);
    }

    void balanceAVL(PNod nod){
        if (nod == NULL || nod->parent == NULL || nod->parent->parent == NULL)
            return;

        PNod parent = nod->parent;
        PNod grandParent = nod->parent->parent;

        nodeHeight(grandParent);

        int BF = grandParent->balanceFactor;

        if (BF < -1 && nod->key < parent->key)
            rotateRight(nod->parent);

        if (BF > 1 && nod->key > parent->key)
            rotateLeft(nod->parent);

        if (BF < -1 && nod->key > parent->key) {
            rotateLeft(nod);
            rotateRight(nod);
        }

        if (BF > 1 && nod->key < parent->key) {
            rotateRight(nod);
            rotateLeft(nod);
        }
    }

    PNod buildSubs(PNod left, PNod right){
        PNod parcurgere = left;
        PNod parinte = NULL;

        if (left == NULL) return right;
        if (right == NULL) return left;

        if (left->rightChild == NULL) {
            left->rightChild = right;
            right->parent = left;
            nodeHeight(left);
            return left;
        }

        while (parcurgere->rightChild != NULL){
            parinte = parcurgere;
            parcurgere = parcurgere->rightChild;
        }

        parinte->rightChild = parcurgere->leftChild;
        if (parcurgere->leftChild != NULL)
            parcurgere->leftChild->parent = parinte;

        parcurgere->parent = NULL;

        parcurgere->leftChild = left;
        parcurgere->rightChild = right;

        left->parent = parcurgere;
        right->parent = parcurgere;

        while (parinte != parcurgere){
            nodeHeight(parinte);
            parinte = parinte->parent;
        }
        nodeHeight(parcurgere);

        return parcurgere;
    }

public:
    AVL(){
        this->root = NULL;
        this->size = 0;
    }

    void afisareNod(PNod nod){
        if (nod == NULL)
            return;
        if (nod->parent == NULL){
            cout<<"ROOT"<<" node_key: "<<nod->key<<" height: "<<nod->height<<" BF: "<<nod->balanceFactor<<endl;
        }
        else{
            cout<<"node_key: "<<nod->key<<" parent_key: "<<nod->parent->key<<" height: "<<nod->height<<" BF: "<<nod->balanceFactor<<endl;
        }
        afisareNod(nod->leftChild);
        afisareNod(nod->rightChild);
    }

    PNod keySearch(long long int key){
        PNod aux = root;

        while (aux != NULL){
            if (aux->key == key)
                return aux;
            if (key < aux->key)
                aux = aux->leftChild;
            else aux = aux->rightChild;
        }

        return NULL;
    }

    void insertElement(long long int key, long long int value = 0){
        PNod newNode = createNod(key, value);
        if (root == NULL){
            this->root = newNode;
            return;
        }
        PNod p = this->root, parent = NULL;
        while (p != NULL){
            parent = p;
            if (p->key < newNode->key){
                p = p->rightChild;
            }
            else p = p->leftChild;
        }

        if (parent->key < newNode->key){
            newNode->parent = parent;
            parent->rightChild = newNode;
            nodeHeight(parent);
        }

        else {
            newNode->parent = parent;
            parent->leftChild = newNode;
            nodeHeight(parent);
        }

        PNod pa = parent;
        while (pa != NULL) {
            nodeHeight(p);
            if (pa->balanceFactor < -1){
                if (pa->leftChild->balanceFactor < 0)
                    balanceAVL(pa->leftChild->leftChild);
                else balanceAVL(pa->leftChild->rightChild);
            }
            else if (pa->balanceFactor > 1) {
                if (pa->rightChild->balanceFactor < 0)
                    balanceAVL(pa->rightChild->leftChild);
                else balanceAVL(pa->rightChild->rightChild);
            }
            pa = pa->parent;
        }
        this->size++;
    }

    void deleteElement(long long int key){
        PNod parcurgere = this->root;
        PNod parent = NULL;

        while (parcurgere != NULL){
            if (key == parcurgere->key){
                break;
            }

            parent = parcurgere;

            if (key < parcurgere->key)
                parcurgere = parcurgere->leftChild;
            else parcurgere = parcurgere->rightChild;
        }

        if (parcurgere == NULL)
            return;

        this->size--;

        PNod new_tree = NULL;
        if (parent == NULL) {
            new_tree = buildSubs(parcurgere->leftChild, parcurgere->rightChild);
            this->root = new_tree;
            if (this->root != NULL) {
                this->root->parent = NULL;
            }
            delete parcurgere;
            return;
        } else {
            if (parcurgere->rightChild == NULL && parcurgere->leftChild == NULL)
                new_tree = NULL;
            else
                new_tree = buildSubs(parcurgere->leftChild, parcurgere->rightChild);
            if (parent->rightChild != NULL && parent->rightChild->key == key) {
                parent->rightChild = new_tree;
                if (new_tree != NULL)
                    new_tree->parent = parent;
            } else {
                parent->leftChild = new_tree;
                if (new_tree != NULL)
                    new_tree->parent = parent;
            }
            PNod p = parent;
            while (p != NULL) {
                nodeHeight(p);
                if (p->balanceFactor < -1){
                    if (p->leftChild->balanceFactor < 0)
                        balanceAVL(p->leftChild->leftChild);
                    else balanceAVL(p->leftChild->rightChild);
                }
                else if (p->balanceFactor > 1) {
                    if (p->rightChild->balanceFactor < 0)
                        balanceAVL(p->rightChild->leftChild);
                    else balanceAVL(p->rightChild->rightChild);
                }
                p = p->parent;
            }

            delete parcurgere;

            return;
        }
    }

    void celmaimare (long long x, long long &mic){
        PNod parcurgere = this->root;
        long long int anterior;

        if (this->root == NULL)
            return;

        while (parcurgere != NULL){
            if (parcurgere->key <= x){
                anterior = parcurgere->key;
                parcurgere = parcurgere->rightChild;
            }
            else parcurgere = parcurgere->leftChild;
            }

        mic = anterior;
    }

    void printAVL(){
        afisareNod(root);
        cout<<endl;
    }

    void celmaimic (long long x, long long &mare){
        PNod parcurgere = this->root;
        long long int anterior;

        if (this->root == NULL)
            return;

        while (parcurgere != NULL) {
            if (parcurgere->key >= x) {
                anterior = parcurgere->key;
                parcurgere = parcurgere->leftChild;
            } else parcurgere = parcurgere->rightChild;
        }

        mare = anterior;
    }

    void interval(long long x, long long y, ofstream& g, PNod curent){
        if (curent == NULL)
            return;
        interval(x, y, g, curent->leftChild);
        if (curent->key >= x && curent->key <= y)
            g<<curent->key<<" ";
        interval(x, y, g, curent->rightChild);
    }

    PNod getRoot() {return this->root;}
};





int main() {
    AVL avl;

    ifstream f("abce.in");
    ofstream g("abce.out");

    long long int operatii;
    f>>operatii;

    for (long long int i=0; i<operatii; i++) {
        long long int operatie;
        f>>operatie;
        switch (operatie) {
            case 1:{
                long long int x;
                f>>x;
                avl.insertElement(x);
                break;
            }
            case 2:{
                long long int x;
                f>>x;
                avl.deleteElement(x);
                break;
            }
            case 3:{
                long long int x;
                f>>x;
                if (avl.keySearch(x) != NULL)
                    g<<1<<endl;
                else g<<0<<endl;
                break;
            }
            case 4:{
                long long int x;
                f>>x;
                long long int pre = 0;
                avl.celmaimare(x, pre);
                g<<pre<<endl;
                break;
            }
            case 5:{
                long long int x;
                f>>x;
                long long int pre = 0;
                avl.celmaimic(x, pre);
                g<<pre<<endl;
                break;
            }
            case 6:{
                long long int x, y;
                f>>x>>y;
                avl.interval(x, y, g, avl.getRoot());
                g<<endl;
                break;
            }
        }
    }

    f.close();
    g.close();

    return 0;
}

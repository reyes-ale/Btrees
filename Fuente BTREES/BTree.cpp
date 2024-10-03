#include "BTree.h"
#include <iostream>
using namespace std;
BTree::BTree(int _t) {
    root = nullptr;
    t = _t;
}


void BTree::traverse() {
    if (root != nullptr)
        traverse(root);
}

void BTree::traverse(BTreeNode* node) {
    int i;
    for (i = 0; i < node->num_claves; i++) {
        if (!node->leaf)
            traverse(node->C[i]); // C es el arreglo de punteros a sus hijos
        cout << " " << node->keys[i];
    }

    if (!node->leaf)
        traverse(node->C[i]);
}


BTreeNode* BTree::search(int k) {
    if (root == nullptr) {
        return nullptr;
    }
    else {
        return search(root, k);
    }
}

BTreeNode* BTree::search(BTreeNode* node, int k) {
    int i = 0;
    while (i < node->num_claves && k > node->keys[i])
        i++;

    if (i < node->num_claves && node->keys[i] == k)
        return node;

    if (node->leaf)
        return nullptr;

    return search(node->C[i], k);
}


void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->num_claves = 1;
    }
    else {
        if (root->num_claves == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->C[0] = root;
            splitChild(s, 0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            insertNonFull(s->C[i], k);

            root = s;
        }
        else {
            insertNonFull(root, k);
        }
    }
}

void BTree::insertNonFull(BTreeNode* node, int k) {
    int i = node->num_claves - 1;

    if (node->leaf) {
        while (i >= 0 && node->keys[i] > k) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->num_claves = node->num_claves + 1;
    }
    else {
        while (i >= 0 && node->keys[i] > k)
            i--;

        if (node->C[i + 1]->num_claves == 2 * t - 1) {
            splitChild(node, i + 1, node->C[i + 1]);

            if (node->keys[i + 1] < k)
                i++;
        }
        insertNonFull(node->C[i + 1], k);
    }
}


void BTree::splitChild(BTreeNode* parent, int i, BTreeNode* antiguo) {
    BTreeNode* nuevo = new BTreeNode(antiguo->t, antiguo->leaf);
    nuevo->num_claves = t - 1;

    for (int j = 0; j < t - 1; j++)
        nuevo->keys[j] = nuevo->keys[j + t];

    if (!antiguo->leaf) {
        for (int j = 0; j < t; j++)
            nuevo->C[j] = antiguo->C[j + t];
    }

    antiguo->num_claves = t - 1;

    for (int j = parent->num_claves; j >= i + 1; j--)
        parent->C[j + 1] = parent->C[j];

    parent->C[i + 1] = nuevo;

    for (int j = parent->num_claves - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = antiguo->keys[t - 1];
    parent->num_claves = parent->num_claves + 1;
}

void BTree::eliminar(BTreeNode* nodo, int k) {
    int idx = 0;
    while (idx < nodo->num_claves && nodo->keys[idx] < k)
        idx++;

    if (idx < nodo->num_claves && nodo->keys[idx] == k) {
        if (nodo->leaf)
            eliminarDeHoja(nodo, idx);
        else
            eliminarDeNoHoja(nodo, idx);
    }
    else {
        if (nodo->leaf) {
            std::cout << "La clave " << k << " no está en el árbol\n";
            return;
        }

        bool flag = (idx == nodo->num_claves);
        if (nodo->C[idx]->num_claves < t)
            llenar(nodo, idx);

        if (flag && idx > nodo->num_claves)
            eliminar(nodo->C[idx - 1], k);
        else
            eliminar(nodo->C[idx], k);
    }
}

int BTree::obtenerPredecesor(BTreeNode* nodo, int idx) {
    BTreeNode* cur = nodo->C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->num_claves];
    return cur->keys[cur->num_claves - 1];
}

int BTree::obtenerSucesor(BTreeNode* nodo, int idx) {
    BTreeNode* cur = nodo->C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}


void BTree::llenar(BTreeNode* nodo, int idx) {
    if (idx != 0 && nodo->C[idx - 1]->num_claves >= t)
        tomarPrestadoDePrevio(nodo, idx);
    else if (idx != nodo->num_claves && nodo->C[idx + 1]->num_claves >= t)
        tomarPrestadoDeSiguiente(nodo, idx);
    else {
        if (idx != nodo->num_claves)
            fusionar(nodo, idx);
        else
            fusionar(nodo, idx - 1);
    }
}
void BTree::fusionar(BTreeNode* nodo, int idx) {
    BTreeNode* hijo = nodo->C[idx];
    BTreeNode* hermano = nodo->C[idx + 1];

    hijo->keys[t - 1] = nodo->keys[idx];

    for (int i = 0; i < hermano->num_claves; ++i)
        hijo->keys[i + t] = hermano->keys[i];

    if (!hijo->leaf) {
        for (int i = 0; i <= hermano->num_claves; ++i)
            hijo->C[i + t] = hermano->C[i];
    }

    for (int i = idx + 1; i < nodo->num_claves; ++i)
        nodo->keys[i - 1] = nodo->keys[i];

    for (int i = idx + 2; i <= nodo->num_claves; ++i)
        nodo->C[i - 1] = nodo->C[i];

    hijo->num_claves += hermano->num_claves + 1;
    nodo->num_claves--;

    delete hermano;
}

void BTree::tomarPrestadoDePrevio(BTreeNode* nodo, int idx) {
    BTreeNode* hijo = nodo->C[idx];
    BTreeNode* hermano = nodo->C[idx - 1];

    for (int i = hijo->num_claves - 1; i >= 0; --i)
        hijo->keys[i + 1] = hijo->keys[i];

    if (!hijo->leaf) {
        for (int i = hijo->num_claves; i >= 0; --i)
            hijo->C[i + 1] = hijo->C[i];
    }

    hijo->keys[0] = nodo->keys[idx - 1];
    if (!nodo->leaf)
        hijo->C[0] = hermano->C[hermano->num_claves];

    nodo->keys[idx - 1] = hermano->keys[hermano->num_claves - 1];
    hijo->num_claves++;
    hermano->num_claves--;
}
void BTree::tomarPrestadoDeSiguiente(BTreeNode* nodo, int idx) {
    BTreeNode* hijo = nodo->C[idx];
    BTreeNode* hermano = nodo->C[idx + 1];

    hijo->keys[hijo->num_claves] = nodo->keys[idx];

    if (!hijo->leaf)
        hijo->C[hijo->num_claves + 1] = hermano->C[0];

    nodo->keys[idx] = hermano->keys[0];

    for (int i = 1; i < hermano->num_claves; ++i)
        hermano->keys[i - 1] = hermano->keys[i];

    if (!hermano->leaf) {
        for (int i = 1; i <= hermano->num_claves; ++i)
            hermano->C[i - 1] = hermano->C[i];
    }

    hijo->num_claves++;
    hermano->num_claves--;
}




// Divide el hijo C[i] del nodo
void BTree::dividirHijo(BTreeNode* nodo, int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(t, y->leaf);
    for (int j = 0; j < t - 1; ++j)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; ++j)
            z->C[j] = y->C[j + t];
    }

    y->num_claves = t - 1;
    for (int j = nodo->num_claves; j >= i + 1; --j)
        nodo->C[j + 1] = nodo->C[j];

    nodo->C[i + 1] = z;

    for (int j = nodo->num_claves - 1; j >= i; --j)
        nodo->keys[j + 1] = nodo->keys[j];

    nodo->keys[i] = y->keys[t - 1];
    nodo->num_claves++;
}

// Inserta una clave en un nodo no lleno
void BTree::insertarEnNoLleno(BTreeNode* nodo, int k) {
    int i = nodo->num_claves - 1;
    if (nodo->leaf) {
        while (i >= 0 && nodo->keys[i] > k) {
            nodo->keys[i + 1] = nodo->keys[i];
            --i;
        }
        nodo->keys[i + 1] = k;
        nodo->num_claves++;
    }
    else {
        while (i >= 0 && nodo->keys[i] > k)
            --i;

        if (nodo->C[i + 1]->num_claves == 2 * t - 1) {
            dividirHijo(nodo, i + 1, nodo->C[i + 1]);
            if (nodo->keys[i + 1] < k)
                ++i;
        }
        insertarEnNoLleno(nodo->C[i + 1], k);
    }
}
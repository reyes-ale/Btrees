#pragma once
class BTreeNode
{
    int* keys;      // Arreglo de claves
    int t;          // Grado mínimo
    BTreeNode** C;  // Arreglo de punteros a hijos
    int num_claves;          // Número actual de claves
    bool leaf;      // True si es un nodo hoja

public:
    BTreeNode(int _t, bool _leaf);
    ~BTreeNode();
    friend class BTree;
};


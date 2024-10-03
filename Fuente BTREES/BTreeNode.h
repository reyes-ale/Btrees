#pragma once
class BTreeNode
{
    int* keys;      // Arreglo de claves
    int t;          // Grado m�nimo
    BTreeNode** C;  // Arreglo de punteros a hijos
    int num_claves;          // N�mero actual de claves
    bool leaf;      // True si es un nodo hoja

public:
    BTreeNode(int _t, bool _leaf);
    ~BTreeNode();
    friend class BTree;
};


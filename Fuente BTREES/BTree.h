#pragma once
#include "BTreeNode.h"
class BTree
{
    BTreeNode* root; // Puntero a la raíz
    int t;           // Grado mínimo

public:

    BTree(int _t);


    void traverse();


    BTreeNode* search(int k);

    void insert(int k);

private:
    
    void traverse(BTreeNode* node);

   
    BTreeNode* search(BTreeNode* node, int k);


    void insertNonFull(BTreeNode* node, int k);


    void splitChild(BTreeNode* parent, int i, BTreeNode* y);

    void eliminar(BTreeNode* nodo, int k);
    int obtenerPredecesor(BTreeNode* nodo, int idx);
    int obtenerSucesor(BTreeNode* nodo, int idx);
    void llenar(BTreeNode* nodo, int idx);
    void tomarPrestadoDePrevio(BTreeNode* nodo, int idx);
    void tomarPrestadoDeSiguiente(BTreeNode* nodo, int idx);
    void fusionar(BTreeNode* nodo, int idx);
    void eliminarDeNoHoja(BTreeNode* nodo, int idx);
    void eliminarDeHoja(BTreeNode* nodo, int idx);
    void dividirHijo(BTreeNode* nodo, int i, BTreeNode* y);
    void insertarEnNoLleno(BTreeNode* nodo, int k);
};



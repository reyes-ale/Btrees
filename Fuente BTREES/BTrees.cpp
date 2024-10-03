#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"
using namespace std;
int main()
{
    BTree t(3); // Un BTree con grado mínimo 3

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    std::cout << "Recorrido del arbol B:\n";
    t.traverse();

    int k = 6;
    (t.search(k) != nullptr) ? std::cout << "\nClave " << k << " encontrada\n" : std::cout << "\nClave " << k << " no encontrada\n";

    k = 15;
    (t.search(k) != nullptr) ? std::cout << "\nClave " << k << " encontrada\n" : std::cout << "\nClave " << k << " no encontrada\n";

    return 0;
}


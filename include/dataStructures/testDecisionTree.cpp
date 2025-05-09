#include <iostream>
#include "decisionTree.hpp"

int main() {
    DecisionTree arbol;
    arbol.insertar("Ajo");
    arbol.insertar("Berenjena");
    arbol.insertar("Calabaza");
    arbol.insertar("Calabazin");
    arbol.insertar("Tomate");

    std::cout << "Buscar: " << arbol.buscar("Tomate") << "\n";

    std::cout << "Recorrido :\n";
    arbol.recorrerPreorden();

    arbol.eliminar("Tomate");
    std::cout << "Elimino Tomate\n";
    arbol.recorrerPreorden();

    return 0;
}

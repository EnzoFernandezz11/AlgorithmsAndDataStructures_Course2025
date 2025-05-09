#include <iostream>
struct Nodo {
    std::string decision;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(const std::string& d)
        : decision(d), izquierda(nullptr), derecha(nullptr) {}
    };
    
#ifndef DECISIONTREE_HPP
#define DECISIONTREE_HPP

class DecisionTree {
    public:
    
        DecisionTree();
        ~DecisionTree();
    
        void insertar(const std::string& decision);
        bool buscar(const std::string& decision) const;
        void eliminar(const std::string& decision);
        bool estaVacio() const;
        void recorrerPreorden() const;
    
    private:
        Nodo* raiz;
    
        void insertar(Nodo*& nodo, const std::string& decision);
        bool buscar(Nodo* nodo, const std::string& decision) const;
        void eliminarNodo(Nodo*& nodo, const std::string& decision);
        void recorrerPreorden(Nodo* nodo) const;
        void destruir(Nodo* nodo);
    };

#endif 
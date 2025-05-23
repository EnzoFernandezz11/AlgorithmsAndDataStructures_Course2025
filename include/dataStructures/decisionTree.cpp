#include "decisionTree.hpp"
#include <iostream>
#include <queue>

DecisionTree::DecisionTree() {
    m_root = nullptr;
}

DecisionTree::~DecisionTree() {
    destruir(m_root);
    m_root = nullptr;
}

void DecisionTree::destruir(Nodo* nodo) {
    if (nodo == nullptr) return;
    destruir(nodo->izquierda);
    destruir(nodo->derecha);
    delete nodo;
    
}


void DecisionTree::insertar(const std::string& decision) {
    insertar(m_root, decision);
}

void DecisionTree::insertar(Nodo*& nodo, const std::string& decision) {
    if (nodo == nullptr) {
        nodo = new Nodo(decision);
        return;
    }

    if (decision < nodo->decision) {
        insertar(nodo->izquierda, decision);
    } else {
        insertar(nodo->derecha, decision);
    }
}


bool DecisionTree::buscar(const std::string& decision) const
{
    //USO BFS PARA LA BUSQUEDA
    if (m_root == nullptr) {
        std::cout << "El árbol está vacío\n";
        return false;
    }

    std::queue<Nodo*> frontier;
    frontier.push(m_root);

    while (!frontier.empty()) {
        Nodo* actual = frontier.front();
        frontier.pop();

        if (actual->decision == decision) {
            return true;
        }

        if (actual->izquierda != nullptr) {
            frontier.push(actual->izquierda);
        }
        if (actual->derecha != nullptr) {
            frontier.push(actual->derecha);
        }
    }

    return false; 

}

void DecisionTree::eliminar(const std::string& decision){
    //USO BFS PARA LA BUSQUEDA
    if (m_root == nullptr) {
        std::cout << "El árbol está vacío\n";
        return;
    }

    std::queue<Nodo*> frontier;
    frontier.push(m_root);

    while (!frontier.empty()) {
        Nodo* actual = frontier.front();
        frontier.pop();

        if (actual->decision == decision) {
            actual->decision = "";
            return;
        }

        if (actual->izquierda != nullptr) {
            frontier.push(actual->izquierda);
        }
        if (actual->derecha != nullptr) {
            frontier.push(actual->derecha);
        }
    }

    return;
}

bool DecisionTree::estaVacio() const
{
    if(m_root == nullptr)
    {
        return true;
    }
    return false;
}

void DecisionTree::recorrerPreorden(Nodo* nodo) const
{
    if(nodo == nullptr)
    {
        return;
    }

    std::cout<< nodo->decision;
    recorrerPreorden(nodo->izquierda);
    recorrerPreorden(nodo->derecha);
}

void DecisionTree::recorrerPreorden() const
{
    recorrerPreorden(m_root);
}




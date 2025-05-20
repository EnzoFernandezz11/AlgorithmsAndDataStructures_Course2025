#include "avlTree.hpp"
#include <queue>

int AVLTree::getHeight(Node* node) {
    if(node == NULL)
        return -1;
    return std::max(getHeight(node->l),getHeight(node->r)) +1;
}

int AVLTree::getBalance(Node* node){
    if(node == NULL)
        return -1;
    return getHeight(node->l) - getHeight(node->r);
}

void AVLTree::actHeight(Node* n){
    if (n==nullptr) {
        return;
    }
    n->height = 1 + std::max(getHeight(n->l), getHeight(n->r));
}

Node* AVLTree::rightRotation(Node* node){
    Node* rot = node->l;
    Node* T2 = rot->r;

    rot->r = node;
    node->l = T2;

    actHeight(rot);
    actHeight(node);

    return rot;

}

Node* AVLTree::leftRotation(Node* node){
    Node* rot = node->r;
    Node* T2 = rot->l;

    rot->l = node;
    node->r = T2;

    actHeight(rot);
    actHeight(node);

    return rot;
}

Node* AVLTree::insert(Node* nodo, int outpostId, int priority){
    if(nodo == NULL) return new Node(outpostId,priority);

    if(priority <= nodo->priority)
        nodo->l = insert(nodo->l,outpostId,priority);
    else if(priority > nodo->priority)
        nodo->r = insert(nodo->r,outpostId,priority);
    else
        return nodo;
    
    actHeight(nodo);

    int b = getBalance(nodo);

    if (b > 1 && priority < nodo->l->priority)
        return rightRotation(nodo);

    if (b < -1 && priority > nodo->r->priority)
         return leftRotation(nodo);

    if (b > 1 && priority > nodo->l->priority) {
        nodo->l = leftRotation(nodo->l);
        return rightRotation(nodo);
    }

    if (b < -1 && priority < nodo->r->priority) {
        nodo->r = rightRotation(nodo->r);
        return leftRotation(nodo);
    }

    return nodo;

}

int AVLTree::findMin(Node* node){
    if(node == NULL)
        return -1;

    else if(node->l == NULL)
        return node->outpostId;

    return findMin(node->l);
}

Node* AVLTree::findMinNode(Node* node){
    if(node == NULL)
        return;

    else if(node->l == NULL)
        return node;

    return findMinNode(node->l);
}

int AVLTree::findMax(Node* node){
    if(node == NULL)
        return -1;
        
    else if(node->r == NULL)
        return node->outpostId;

    return findMin(node->r);
}

bool AVLTree::contains(int outpostId){

    if(m_root == NULL){
        std::cout<<"Arbol vacio"<<"\n";
        return false;
    }

    std::queue<Node*> frontier;
    frontier.push(m_root);

    while(!frontier.empty())
    {
        Node* temp = frontier.front();
        frontier.pop();

        if(temp->outpostId == outpostId)
            return true;
        
        if(temp->l != NULL)
            frontier.push(temp->l);
        if(temp->r != NULL)
            frontier.push(temp->r);
    }
    return false;

}

void AVLTree::LRD(Node* node){
    if (node == NULL)
        return;

    LRD(node->l); // 
    std::cout << node->outpostId << " - "; 
    LRD(node->r); 

}

void AVLTree::printInOrder(){

    LRD(m_root);
}

int AVLTree::countNodes(Node* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->l) + countNodes(node->r);
}

void AVLTree::printStats(){
    int totalNodos = countNodes(m_root);
    int altura = getHeight(m_root);

    std::cout << "Cantidad de nodos: " << totalNodos << "\n";
    std::cout << "Altura del árbol: " << altura << "\n";

}

Node* AVLTree::remove(Node* nodo, int outpostId){

    std::queue<Node*> frontier;
    frontier.push(nodo);

    while(!frontier.empty())
    {
        if(nodo->outpostId == outpostId)
        {

            if(nodo->l == NULL && nodo->r == NULL)
                delete nodo;
            else if(nodo->l == NULL)
            {
                Node* temp = nodo;
                nodo = nodo->r;
                delete temp;
            }
            else if(nodo->r == NULL)
            {
                Node* temp = nodo;
                nodo = nodo->r;
                delete temp;
            }
            else
            {
                Node* temp = findMinNode(nodo->r);
                nodo->outpostId = temp->outpostId;
                nodo->priority = temp->priority;
                nodo->r = remove(nodo->r, temp->outpostId);

            }


        }
        if(nodo->l != NULL)
            frontier.push(nodo->l);
        if(nodo->r != NULL)
            frontier.push(nodo->r);
    }


}
#include <iostream>

struct Node {
    int outpostId;
    int priority;
    int height;
    Node* l;
    Node* r;
    Node(int id, int p) : outpostId(id), priority(p), height(0), l(nullptr), r(nullptr) {}
};

#ifndef AVLTREE_HPP
#define AVLTREE_HPP

class AVLTree {
    private:
        Node* m_root;
        int getHeight(Node* node); //
        int getBalance(Node* node);//
        Node* rightRotation(Node* node);//
        Node* leftRotation(Node* node);//
        void actHeight(Node* n);//
        Node* insert(Node* nodo, int outpostId, int priority);//
        Node* remove(Node* nodo,int outpostId); //
        int findMin(Node* node);//
        int findMax(Node* node);//
        void LRD(Node* node); //
        int countNodes(Node* node);//
        Node* AVLTree::findMinNode(Node* node);//
        void destruir(Node* node);

    public:
        AVLTree();
        ~AVLTree();
        void insert(int outpostId, int priority); //
        void remove(int outpostId);
        bool contains(int outpostId); //
        int findMin();//
        int findMax();//
        void printInOrder(); //
        void printStats();  // 
        
        
};

#endif
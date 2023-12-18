//
// Created by fotop on 28/10/2023.
//


#ifndef AVL_AVL_H
#define AVL_AVL_H

/**
 * @author Adrián González Pérez agp00118@red.ujaen.es
 */

#include <stdexcept>
#include <iostream>
#include "Dynamic_container.h"

/**
 * @brief Class which will serve as a data structure similar to AVL Tree
 * @tparam T Template class object
 */
template <class T>
class AVL {
private:

    //--------------------START OF--------------------
    //-------------NODE AVL PRIVATE CLASS-------------
    /**
     * @brief Private Class which will store correctly the data of the AVL Tree
     * @tparam U Template class object
     */
    template<class U>
            class NodeAVL{
            public:
                NodeAVL<U>* left;
                NodeAVL<U>* right;
                U data;
                char balance;

                /**
                 * @brief Default constructor. Returns a NodeAVL object "empty"
                 */
                NodeAVL() { left = nullptr;
                            right = nullptr;
                            data = U();
                            balance = 0;
                }

                /**
                 * @brief Constructor. Returns a NodeAVL object with given data
                 * @param _data Data to store in the AVL
                 */
                NodeAVL(U& _data){
                    data = _data;
                    balance = 0;
                    left = nullptr;
                    right = nullptr;
                }

                /**
                 *
                 * @param _data Data to store in the AVL
                 * @param _balance Balance of NodeAVL. It's a param that helps the AVL to balance the height of each NodeAVL in the AVL
                 */
                NodeAVL(U& _data, char _balance){
                    data = _data;
                    balance = _balance;
                    left = nullptr;
                    right = nullptr;
                }
            };

    //---------------------END OF---------------------
    //-------------NODE AVL PRIVATE CLASS-------------

private:
    NodeAVL<T>* root;
    unsigned int size;

    void copyRootLeftRightPath(NodeAVL<T>* &node, NodeAVL<T>* other_node);

    void delLeftRightRootPath(NodeAVL<T>* &node);

    void leftRotation(NodeAVL<T>* &node);

    void rightRotation(NodeAVL<T>* &node);

    bool push(NodeAVL<T>* &node, T &data);

    void recSearch (NodeAVL<T>* &node, T& data, T* &found);

    T* itSearch (NodeAVL<T>* node, T& data);

    void readLeftRootRightPath(NodeAVL<T> *node, Dynamic_container<T*> &array);

    unsigned int heightLeftRootRightPath(NodeAVL<T> *node);

public:
    AVL() { root = nullptr;
            size = 0;
    }
    AVL(const AVL &other);

    AVL& operator=(const AVL<T> &other);

    bool push(T &data);

    T* itSearch(T& data);

    T* recSearch(T& data);

    Dynamic_container<T*> readAVL();

    const unsigned int sizeAVL();

    unsigned int height();

    ~AVL();

};


//-----------START OF THE PRIVATE METHODS OF AVL TREE-----------
/**
 * @brief Recursive private method used for copy all the data of other AVL Tree in this AVL Tree. NOTE: It does a deep copy
 * @param node This AVL Tree's node
 * @param other_node Other AVL Tree's node which will be copied
 */
template <class T>
void AVL<T>::copyRootLeftRightPath(NodeAVL<T>* &node, NodeAVL<T>* other_node) {
    if (other_node){
        node = new NodeAVL<T>(other_node->data,other_node->balance);
        copyRootLeftRightPath(node->left,other_node->left);
        copyRootLeftRightPath(node->right,other_node->right);
    }
}

/**
 * @brief Recursive private method used for delete all the data stored by this AVL Tree
 * @param node This AVL Tree's node
 */
template <class T>
void AVL<T>::delLeftRightRootPath(NodeAVL<T> *&node) {
    if(node){
        delLeftRightRootPath(node->left);
        delLeftRightRootPath(node->right);

        delete node;
        size--;
    }
}

/**
 * @brief Private method used for do internal modifications to the structure of this AVL Tree and keep it balanced after insertions. It makes rotations to the left
 * @param node This AVL Tree's node which will be rotated because it is unbalanced after an insertion.
 */
template <class T>
void AVL<T>::leftRotation(NodeAVL<T> *&node) {
    NodeAVL<T> *newRoot = node;
    NodeAVL<T> *newRight = nullptr;

    node = newRight = newRoot->right;
    newRoot->right = newRight->left;
    newRight->left = newRoot;
    newRoot->balance++;
    if (newRight->balance < 0)
        newRoot->balance -= newRight->balance;
    newRight->balance++;
    if (newRoot->balance > 0)
        newRight->balance += newRoot->balance;
}

/**
 * @brief Private method used for do internal modifications to the structure of this AVL Tree and keep it balanced after insertions. It makes rotations to the right
 * @param node This AVL Tree's node which will be rotated because it is unbalanced after an insertion.
 */
template <class T>
void AVL<T>::rightRotation(NodeAVL<T> *&node) {
    NodeAVL<T> *newRoot = node;
    NodeAVL<T> *newLeft = nullptr;

    node = newLeft = newRoot->left;
    newRoot->left = newLeft->right;
    newLeft->right = newRoot;
    newRoot->balance--;
    if (newLeft->balance > 0)
        newRoot->balance -= newLeft->balance;
    newLeft->balance--;
    if (newRoot->balance < 0)
        newLeft->balance += newRoot->balance;
}

/**
 * @brief Private method to insert given data inside this AVL Tree.
 * @param node This AVL Tree's node which will contain the new data.
 * @param data Data to be stored inside this AVL Tree
 * @return Param heightChanged which indicate if the push node modify balance in this AVL Tree's structure
 */
template <class T>
bool AVL<T>::push(NodeAVL<T> *&node, T &data) {
    NodeAVL<T> *aux = node;
    bool heightChanged = false;

    if(!aux){
        aux = new NodeAVL<T>(data);
        node = aux;
        heightChanged = true;
        size++;
    }
    else if (data != aux->data){
        if (data > aux->data){
            if (push(aux->right, data)){
                aux->balance--;
                if (aux->balance == -1)
                    heightChanged = true;
                else if (aux->balance == -2){
                    if (aux->right->balance == 1)
                        rightRotation(aux->right);
                    leftRotation(node);
                }
            }
        }
        else if (data < aux->data){
            if (push(aux->left, data)){
                aux->balance++;
                if (aux->balance == 1)
                    heightChanged = true;
                else if (aux->balance == 2){
                    if (aux->left->balance == -1)
                        leftRotation(aux->left);
                    rightRotation(node);
                }
            }
        }
    }
    else
        std::cout << "---NOTE---:IN AVL<T>::push(T data): The given data, '"<< data <<"' already exists in the AVL map. Has not been inserted" << std::endl;
    return heightChanged;
}

template <class T>
void AVL<T>::recSearch(NodeAVL<T>* &node, T &data, T* &found) {
    if (node){
        if (node->data == data){
            found = &node->data;
        }
        else if (node->data > data)
            recSearch(node->left, data, found);
        else
            recSearch(node->right, data, found);
    }
}

template <class T>
T* AVL<T>::itSearch(NodeAVL<T> *node, T &data) {
    while (node){
        if(node->data == data){
            return &node->data;
        }
        else if (node->data < data)
            node = node->right;
        else if (node->data > data)
            node = node->left;
    }
    return nullptr;
}

template <class T>
void AVL<T>::readLeftRootRightPath(NodeAVL<T> *node, Dynamic_container<T *> &array) {
    if (node){
        readLeftRootRightPath(node->left,array);
        array.push(&node->data);
        readLeftRootRightPath(node->right,array);
    }
}

template <class T>
Dynamic_container<T*> AVL<T>::readAVL() {
    Dynamic_container<T*> result;
    readLeftRootRightPath(root,result);
    return result;
}

template <class T>
unsigned int AVL<T>::heightLeftRootRightPath(NodeAVL<T> *node) {
    if (node){
        unsigned int left_height = heightLeftRootRightPath(node->left) + 1;
        unsigned int right_height = heightLeftRootRightPath(node->right) + 1;

        if(left_height >= right_height)
            return left_height;
        return right_height;
    }
    else
        return 0;
}










template <class T>
AVL<T>::AVL(const AVL<T> &other) {
    copyRootLeftRightPath(this->root, other.root);
    this->size = other.size;
}

template <class T>
AVL<T>& AVL<T>::operator=(const AVL<T> &other) {
    if(this == &other){
        throw std::invalid_argument("---FATAL ERROR--- in AVL<T>::operator=(const AVL<T>) ---- Left operand can't have same memory alloc than the left one.");
    }
    //Empty this object
    delLeftRightRootPath(this->root);

    //Copy the other object
    copyRootLeftRightPath(this->root, other.root);
    this->size = other.size;

    return *this;
}

template <class T>
bool AVL<T>::push(T &data) {
    unsigned int aux_size = size;
    push(root,data);
    if (aux_size == size)
        return true;
    return false;
}

template <class T>
T* AVL<T>::recSearch(T &data) {
    T* found = nullptr;
    recSearch(root, data, found);
    if (found)
        return found;
    else
        throw std::invalid_argument("---ERROR--- in AVL<T>:recSearch(T& data) ---- The given data does not belong to the tree.");
}

template <class T>
T* AVL<T>::itSearch(T &data) {
    T* found = itSearch(root,data);
    if (found)
        return found;
    else
        throw std::invalid_argument("---ERROR--- in AVL<T>:recSearch(T& data) ---- The given data does not belong to the tree.");
}

template <class T>
const unsigned int AVL<T>::sizeAVL() {
    return size;
}

template <class T>
unsigned int AVL<T>::height() {
    return heightLeftRootRightPath(root);;
}

template <class T>
AVL<T>::~AVL() {
    delLeftRightRootPath(root);
}



#endif //AVL_AVL_H

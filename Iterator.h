//
// Created by fotop on 12/10/2023.
//

#ifndef PR1_CD_ITERATOR_H
#define PR1_CD_ITERATOR_H

#include "NodeLinkedList.h"

template <class T> class NodeLinkedList;

template <class T>
class Iterator {
 private:
    NodeLinkedList<T>* node;
    friend class Linked_list<T>;
public:
    Iterator(NodeLinkedList<T>* _node) : node(_node) {}

    bool end() { return  node == nullptr; }

    void next() { node = node->next; }

    void set(T& _data) { node->data = _data; }

    T& data () { return node->data; }

    T& operator*() { return node->data; }

    ~Iterator() { node = nullptr; }
};


#endif //PR1_CD_ITERATOR_H

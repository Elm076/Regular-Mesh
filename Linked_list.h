//
// Created by fotop on 10/10/2023.
//

#ifndef PR1_CD_LINKED_LIST_H
#define PR1_CD_LINKED_LIST_H

#include "NodeLinkedList.h"
#include <stdexcept>

template <class T>
class Linked_list {


private:
    NodeLinkedList<T>* header;
    NodeLinkedList<T>* tail;
    unsigned int size;

public:
    Linked_list();

    Linked_list(const Linked_list& other);

    Linked_list& operator=(const Linked_list& other);

    T& get_header();

    T& get_tail();

    unsigned int list_size() const;

    Iterator<T> iterator();

    void push_front(T& _data);

    void push_back(T& _data);

    void push_in_forward(Iterator<T>& i, T& _data);

    void push_in_behind(Iterator<T>& i, T& _data);

    void pop_front();

    void pop_back();

    void pop(Iterator<T>& i);

    Linked_list<T> concatenate(const Linked_list<T>& other);

    ~Linked_list();

};

template <class T>
Linked_list<T>::Linked_list() {
    header = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
Linked_list<T>::Linked_list(const Linked_list<T> &other) {
    this->header = new NodeLinkedList<T>(other.header->data);
    this->tail = this->header;

    NodeLinkedList<T>* iterator_other = other.header->next;
    while(iterator_other != nullptr){
        this->tail->next = new NodeLinkedList<T>(iterator_other->data);
        iterator_other = iterator_other->next;
        this->tail = this->tail->next;
    }
    this->size = other.size;



}

template <class T>
Linked_list<T>& Linked_list<T>::operator=(const Linked_list<T> &other) {

    if(other.list_size() != 0){
        NodeLinkedList<T>* to_delete = header;
        while(header != tail and size != 0){
            header = header->next;
            delete to_delete;
            to_delete = header;
            size--;
        }
    }

    /*
    NodeLinkedList<T>* delete_iterator = this->header->next;

    while (delete_iterator != nullptr){
        delete header;
        size--;
        header = delete_iterator;
        delete_iterator = delete_iterator->next;
    }
    delete header;
    */

    this->header = new NodeLinkedList<T>(other.header->data);

    /*
    NodeLinkedList<T>* iterator_other = other.header->next;
    NodeLinkedList<T>* iterator_this = this->header;
    while(iterator_other != nullptr){
        NodeLinkedList<T>* next_this = new NodeLinkedList<T>(other.header->data);
        iterator_this->next = next_this;
        iterator_other = iterator_other->next;
        iterator_this = iterator_this->next;
    }
    this->tail = iterator_this;
    this->size = other.size;
     */

    this->header = new NodeLinkedList<T>(other.header->data);
    this->tail = this->header;

    NodeLinkedList<T>* iterator_other = other.header->next;
    while(iterator_other != nullptr){
        this->tail->next = new NodeLinkedList<T>(iterator_other->data);
        iterator_other = iterator_other->next;
        this->tail = this->tail->next;
    }
    this->size = other.size;

    return *this;
}

template <class T>
T& Linked_list<T>::get_header() {
    return header->data;
}

template <class T>
T& Linked_list<T>::get_tail() {
    return tail->data;
}

template <class T>
Iterator<T> Linked_list<T>::iterator() {
    return Iterator<T>(header);
}

template <class T>
void Linked_list<T>::push_front(T &_data) {
    if (tail == nullptr){
        header = new NodeLinkedList<T>(_data);
        tail = header;
    }
    else{
        NodeLinkedList<T>* new_header;
        new_header = new NodeLinkedList<T>(_data, header);
        header = new_header;
    }
    size++;

}

template <class T>
void Linked_list<T>::push_back(T &_data) {
    if (header == nullptr){
        tail = new NodeLinkedList<T>(_data);
        header = tail;
    }
    else{
        NodeLinkedList<T>* new_tail;
        new_tail = new NodeLinkedList<T>(_data);
        tail->next = new_tail;
        tail = new_tail;
    }
    size++;
}

template <class T>
void Linked_list<T>::push_in_forward(Iterator<T>& i, T &_data) {
    if (header == i.node){
        push_front(_data);
    }
    else if (header != tail){
        NodeLinkedList<T>* previous_node = header;
        unsigned int count = 0;
        while(count < size and previous_node->next != i.node){
            previous_node = previous_node->next;
            count ++;
        }
        if (count != size){
            previous_node->next = new NodeLinkedList<T>(_data, i.node);
        }
        else{
            throw std::out_of_range("---FATAL ERROR--- Exception ocurred on: Linked_list<T>::push_in_forward(Iterator<T>& i, T &_data). The specified iterator does not contain data stored in this Linked List ---NOT FOUND--- ");
        }
    }
    size++;
}

template <class T>
void Linked_list<T>::push_in_behind(Iterator<T> &i, T &_data) {
    /*maybe here I should check if the iterator belongs to this list but do it will mean this operation would be now O(n) instead O(1)
    I opted for the 0(1) version assuming the iterator belong to this*/
    NodeLinkedList<T>* new_node = new NodeLinkedList<T>(_data, i.node->next);
    i.node->next = new_node;

    size++;
}


template <class T>
void Linked_list<T>::pop_front() {
    if (header == nullptr){
        tail = nullptr;
    }
    else{
        NodeLinkedList<T>* deleted_node = header;
        header = header->next;
        delete deleted_node;
    }
    size--;
}

template <class T>
void Linked_list<T>::pop_back() {
    NodeLinkedList<T>* iterator = tail;
    if (header != tail){
        iterator = header;
        while (iterator->next != tail){
            iterator = iterator->next;
        }
        delete tail;
        iterator->next = nullptr;
        tail = iterator;
        if (tail == nullptr){
            header = nullptr;
        }
    }
    size--;
}

template <class T>
void Linked_list<T>::pop(Iterator<T> &i) {
    NodeLinkedList<T>* target = header;
    while (target->next != i.node){
        target = target->next;
    }

    if(i.node->next == nullptr){
       pop_back();
       //delete i.node;
       i.node = nullptr;
    }
    else if (i.node == header){
        pop_front();
    }
    else{
        i.node = i.node->next;
        delete target->next;
        target->next = i.node;
    }

    size--;
}


template <class T>
unsigned int Linked_list<T>::list_size() const {
    return size;
}


template <class T>
Linked_list<T> Linked_list<T>::concatenate(const Linked_list<T> &other) {
    Linked_list<T> new_list = Linked_list<T>(*this);

    NodeLinkedList<T>* iterator = other.header;

    while(iterator != nullptr){
        new_list.tail->next = new NodeLinkedList<T>(iterator->data);
        new_list.tail = new_list.tail->next;
        iterator = iterator->next;
    }

    return new_list;
}


template <class T>
Linked_list<T>::~Linked_list() {
    NodeLinkedList<T>* to_delete = header;
    while(header != tail and size != 0){
        header = header->next;
        delete to_delete;
        to_delete = header;
        size--;
    }
}

#endif //PR1_CD_LINKED_LIST_H

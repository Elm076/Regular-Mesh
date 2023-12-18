//
// Created by fotop on 12/10/2023.
//

#ifndef PR1_CD_NODE_H
#define PR1_CD_NODE_H

//DECLARATION FORWARD OF THE NEEDED CLASSES

template <class T> class Linked_list;
template <class T> class Iterator;


/*  #################### PRIVATE CLASS OF LINKED LIST ####################
 *  ####################          CLASS NODE          ####################*/

template <class T>
class NodeLinkedList {
private:
    friend class Linked_list<T>;
    friend class Iterator<T>;
    T data;
    NodeLinkedList *next;


    NodeLinkedList() {    T();
                next = nullptr; }

    explicit NodeLinkedList(T& _data, NodeLinkedList* _next = nullptr) :
        data(_data),
        next(_next)
        {}
};

/*  ################ END OF PRIVATE CLASS OF LINKED LIST #################
 *  ####################          CLASS NODE          ####################*/



#endif //PR1_CD_NODE_H

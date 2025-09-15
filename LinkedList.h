#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <functional>

// Node class template
template<typename T>
class Node {

};

template<typename T>
class LinkedList {
private:


public:


    void append(T value) {

    }

    void addFirst(T value) {

    }

    void deleteFirst() {

    }

    void deleteLast() {


    }

    void forEach(std::function<void(const T&, bool)> callback) {
        Node<T>* current = head;
        while (current) {
            bool isLast = (current->next == nullptr);
            callback(current->data, isLast);
            current = current->next;
        }
    }

    ~LinkedList() {

};

#endif // LINKEDLIST_H
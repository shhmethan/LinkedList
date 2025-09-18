#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <functional>

// Node class template
template<typename T>
class Node {
private:
    T data;
    Node<T>* next;

    // Grant LinkedList access to private members
    template<typename> friend class LinkedList;

public:
    Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void append(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (head==nullptr) head = newNode;
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void addFirst(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    void deleteFirst() {
        if (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void deleteLast() {
        if (!head) return;

        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }

        Node<T>* current = head;
        while (current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    void deleteAtIndex(int index) {

        // Else index was out of bounds, do nothing
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
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

#endif // LINKEDLIST_H
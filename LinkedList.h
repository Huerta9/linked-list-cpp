
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <iostream>
using namespace std;
template <class T>

class LinkedList {
public:
    LinkedList(); // Constructor
    ~LinkedList(); // Destructor
    void addFirst(T data);
    void addLast(T data);
    bool add(T data, int pos);
    void deleteFirst();
    void deleteLast();
    void del(int pos);
    bool isEmpty() const;
    int deleteAll();
    T set(T data, int pos);
    T get(int pos) const;
    bool change(int pos1, int pos2);
    int getSize() const;
    void print() const;
    void reverse();
    void shift(int n);
    bool operator==(const LinkedList<T> &other) const;
    LinkedList(const LinkedList<T> &other); // Copy constructor
    void operator+=(const LinkedList<T> &other);
    LinkedList<T> &operator=(const LinkedList<T> &other);
private:
    Node<T> *head;
    int size;
};
template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size = 0;
}
template <class T>
LinkedList<T>::~LinkedList() {
    deleteAll();
}

template <class T>
void LinkedList<T>::addFirst(T data) {
    head = new Node(data, head);
    size++;
}
template <class T>
void LinkedList<T>::addLast(T data) {
    if (isEmpty())
        addFirst(data);
    else {
        Node<T> *aux = head;
        while (aux->getNext() != nullptr)
            aux = aux->getNext();
        aux->setNext(new Node(data));
        size++;
    }
}
template <class T>
bool LinkedList<T>::add(T data, int pos) {
    if (pos > size)
        return false;
    Node<T> *aux = head;
    for (int i=1; i<pos; i++)
        aux = aux->getNext();
    aux->setNext(new Node(data, aux->getNext()));
    size++;
    return true;
}
template <class T>
void LinkedList<T>::deleteFirst() {
    if (head != nullptr) {
        Node<T> *borrar = head;
        head = head->getNext();
        delete borrar;
        size--;
    }
}
template <class T>
void LinkedList<T>::deleteLast() {
    if (size == 1)
        deleteFirst();
    else if (! isEmpty()) {
        Node<T> *aux = head;
        while(aux->getNext()->getNext() != nullptr)
            aux = aux->getNext();
        Node<T> *borrar = aux->getNext();
        aux->setNext(nullptr);
        delete borrar;
        size--;
    }
}
template <class T>
void LinkedList<T>::del(int pos) {
    if (pos == 0)
        deleteFirst();
    else {
        Node<T> *aux = head;
        for (int i=1; i<pos; i++)
            aux = aux->getNext();
        Node<T> *erase = aux->getNext();
        aux->setNext(erase->getNext());
        delete erase;
        size--;
    }
}
template <class T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr;
}
template <class T>
int LinkedList<T>::deleteAll() {
    int erased = size;
    while (! isEmpty())
        deleteFirst();
    return erased;
}
template <class T>
T LinkedList<T>::set(T data, int pos) {
    Node<T> *p = head;
    for(int i=0; i<pos; i++)
        p = p->getNext();
    T previous = p->getData();
    p->setData(data);
    return previous;
}
template <class T>
T LinkedList<T>::get(int pos) const {
    Node<T> *p = head;
    for(int i=0; i<pos; i++)
        p = p->getNext();
    return p->getData();
}
template <class T>
bool LinkedList<T>::change(int pos1, int pos2) {
    if (pos1 == pos2 || pos1 < 0 || pos2 < 0 ||
        pos1 >= size || pos2 >= size)
        return false;
    T temp = get(pos1);
    set(get(pos2), pos1);
    set(temp, pos2);
    return true;
}
template <class T>
int LinkedList<T>::getSize() const {
    return size;
}
template <class T>
void LinkedList<T>::print() const {
    Node<T> *p = head;
    if (p != nullptr) {
        cout << p->getData();
        p = p->getNext();
    }
    while (p != nullptr) {
        cout << " " << p->getData();
        p = p->getNext();
    }
    cout << endl;
}


template <class T>
void LinkedList<T>::reverse() {
    Node<T> *prev = nullptr;
    Node<T> *curr = head;
    while (curr != nullptr) {
        Node<T> *next = curr->getNext(); // Se guarda el siguiente nodo
        curr->setNext(prev); // Se invierte el enlace
        prev = curr;
        curr = next;
    }
    head = prev; // El último nodo original es la nueva cabeza
}

template <class T>
void LinkedList<T>::shift(int n) {
    if (size <= 1)
        return;
    int k = n % size; // Se eliminan las vueltas completas
    if (k < 0)
        k += size; // Un corrimiento negativo equivale a uno positivo
    if (k == 0)
        return;
    // aux queda en el nodo anterior al inicio de los últimos k nodos
    Node<T> *aux = head;
    for (int i=1; i<size-k; i++)
        aux = aux->getNext();
    Node<T> *newHead = aux->getNext();
    aux->setNext(nullptr); // Se corta la lista en dos
    Node<T> *last = newHead;
    while (last->getNext() != nullptr)
        last = last->getNext();
    last->setNext(head); // Los últimos k nodos pasan al inicio
    head = newHead;
}

template <class T>
bool LinkedList<T>::operator==(const LinkedList<T> &other) const {
    if (size != other.size)
        return false;
    Node<T> *a = head;
    Node<T> *b = other.head;
    while (a != nullptr) {
        if (!(a->getData() == b->getData()))
            return false;
        a = a->getNext();
        b = b->getNext();
    }
    return true;
}

// Act 2.2

// Agrega al final una copia de cada dato de other
// Complejidad: O(n + m), n = tamaño original, m = tamaño de other
template <class T>
void LinkedList<T>::operator+=(const LinkedList<T> &other) {
    int count = other.size; // Se guarda por si other es la misma lista
    if (count == 0)
        return;
    Node<T> *last = head;
    if (last != nullptr)
        while (last->getNext() != nullptr)
            last = last->getNext(); // Se busca el último nodo una sola vez
    Node<T> *src = other.head;
    for (int i = 0; i < count; i++) {
        Node<T> *newNode = new Node<T>(src->getData());
        if (last == nullptr)
            head = newNode; // La lista original estaba vacía
        else
            last->setNext(newNode);
        last = newNode;
        size++;
        src = src->getNext();
    }
}

// Deja la lista original como clon de other
// Complejidad: O(n + m), n = tamaño original (se borra), m = tamaño de other
template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other) {
    if (this == &other) // Autoasignación
        return *this;
    deleteAll();
    Node<T> *last = nullptr;
    Node<T> *p = other.head;
    while (p != nullptr) {
        Node<T> *newNode = new Node<T>(p->getData());
        if (last == nullptr)
            head = newNode;
        else
            last->setNext(newNode);
        last = newNode;
        size++;
        p = p->getNext();
    }
    return *this;
}
// Copy constructor: crea nodos nuevos con una copia de cada dato de other
// Complejidad: O(n), n = tamaño de other
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) {
    head = nullptr;
    size = 0;
    Node<T> *last = nullptr;
    Node<T> *p = other.head;
    while (p != nullptr) {
        Node<T> *newNode = new Node<T>(p->getData());
        if (last == nullptr)
            head = newNode; // Primer nodo de la copia
        else
            last->setNext(newNode);
        last = newNode;
        size++;
        p = p->getNext();
    }
}

#endif
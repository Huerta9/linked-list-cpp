//
// Created by Sebastian Huerta on 25/09/26.
//
// Implementa la clase nodo para listas simplemente encadenadas lineales.
// Autor: Santiago Conant
// Fecha: 25 de septiembre de 2026
#ifndef NODE_H
#define NODE_H
template <class T>
class Node {
public:
    Node(T data); // Constructor
    Node(T data, Node<T> *next); // Constructor
    T getData() const;
    Node<T> *getNext() const;
    void setData(T data);
    void setNext(Node<T> *next);
private:
    T data;
    Node<T> *next;
};
template <class T>
Node<T>::Node(T data) {
    this->data = data;
    next = nullptr;
}
template <class T>
Node<T>::Node(T data, Node<T> *next) {
    this->data = data;
    this->next = next;
}
template <class T>
T Node<T>::getData() const {
    return data;
}
template <class T>
Node<T> *Node<T>::getNext() const {
    return next;
}
template <class T>
void Node<T>::setData(T data) {
    this->data = data;
}
template <class T>
void Node<T>::setNext(Node<T> *next) {
    this-> next = next;
}
#endif
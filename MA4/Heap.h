#pragma once
#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <string>
#include <limits>
#include <algorithm> // For sorting

template<typename T>
class Heap {
private:
    std::vector<T> _items; // Heap storage with placeholder at index 0

    void percolateDown(unsigned int hole);
    void percolateUp(int hole);

public:
    Heap();
    void push(T item);
    T pop();
    T peek() const; // Returns min without removing
    bool empty() const;
    long unsigned int size() const;
    void heapify(const std::vector<T>& input); // Converts input into a heap
    std::string to_string() const;
};

// Default constructor
template<typename T>
Heap<T>::Heap() {
    _items.push_back(std::numeric_limits<T>::min()); // Placeholder
}

// Percolate Down
template<typename T>
void Heap<T>::percolateDown(unsigned int hole) {
    unsigned int child;
    T tmp = _items[hole];

    while (hole * 2 <= size()) {
        child = hole * 2;
        if (child != size() && _items[child + 1] < _items[child]) {
            child++;
        }

        if (_items[child] < tmp) {
            _items[hole] = _items[child];
        }
        else {
            break;
        }

        hole = child;
    }
    _items[hole] = tmp;
}

// Percolate Up
template<typename T>
void Heap<T>::percolateUp(int hole) {
    T tmp = _items[hole];

    while (hole > 1 && tmp < _items[hole / 2]) {
        _items[hole] = _items[hole / 2];
        hole /= 2;
    }

    _items[hole] = tmp;
}

// Push item
template<typename T>
void Heap<T>::push(T item) {
    _items.push_back(item);
    percolateUp(_items.size() - 1);
}

// Pop item
template<typename T>
T Heap<T>::pop() {
    if (size() == 0) {
        throw std::out_of_range("pop() - No elements in heap");
    }

    T minItem = _items[1];
    _items[1] = _items.back();
    _items.pop_back();

    if (!empty()) {
        percolateDown(1);
    }

    return minItem;
}

// Peek item
template<typename T>
T Heap<T>::peek() const {
    if (empty()) {
        throw std::out_of_range("peek() - No elements in heap");
    }
    return _items[1];
}

// Empty check
template<typename T>
bool Heap<T>::empty() const {
    return _items.size() == 1;
}

// Heap size
template<typename T>
long unsigned int Heap<T>::size() const {
    return _items.size() - 1;
}

// Heapify input
template<typename T>
void Heap<T>::heapify(const std::vector<T>& input) {
    _items.clear();
    _items.push_back(std::numeric_limits<T>::min());

    for (const T& item : input) {
        _items.push_back(item);
    }

    for (int i = size() / 2; i > 0; --i) {
        percolateDown(i);
    }
}

// To string
template<typename T>
std::string Heap<T>::to_string() const {
    std::string ret;
    for (unsigned int i = 1; i < _items.size(); i++) {
        ret += std::to_string(_items[i]) + " ";
    }
    return ret;
}

#endif

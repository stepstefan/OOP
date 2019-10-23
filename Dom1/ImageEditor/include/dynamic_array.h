// 
// dynamic_array.h
//
// Created by Stefan Stepanovic on 22/10/2019

#pragma once

#include <stdlib.h>

// Default dynamic array class
template<typename T>
class Array
{
public:
    typedef T* iterator;

    // Constructors, destructor
    Array();
    explicit Array(size_t size);
    explicit Array(size_t size, T value);
    Array(const Array<T>& array);
    ~Array();

    // Data access
    inline size_t size() const;
    inline size_t capacity() const;
    inline bool empty() const;
    
    void reserve(size_t capacity);
    void resize(size_t size);
    void shrink_to_fit();   
    
    inline iterator begin();
    inline iterator end();
    inline T& front();
    inline T& back();
    inline const T& front() const;
    inline const T& back() const;

    void push_back(const T& value);
    void pop_back();

    T& operator[](size_t index);
    Array<T>& operator=(const Array<T>&);

private:
    T* data_;
    size_t capacity_;
    size_t size_;
};

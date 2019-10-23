// 
// dynamic_array.cpp
//
// Created by Stefan Stepanovic on 22/10/2019

#include "../include/dynamic_array.h"

// Implementation

// Constructors
template<typename T>
Array<T>::Array()
    : capacity_(0), size_(0)
{
    data_ = new T[0];
}

template<typename T>
Array<T>::Array(size_t size)
    : size_(size), capacity_(size)
{
    data_ = new T[size];
}

template<typename T>
Array<T>::Array(const Array<T>& array)
{
    size_ = array.size();
    capacity_ = array.capacity();
    data_ = new T[capacity_];
    for(size_t idx = 0; idx < size_; ++idx)
    {
        data_[idx] = array[idx];
    }
}
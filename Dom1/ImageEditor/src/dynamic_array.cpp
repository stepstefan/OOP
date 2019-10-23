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
    data_ = new T[size_];
    if (!data_)
    {
        std::cout << "Mem. allocation failed" << std::endl;
    }
}

template<typename T>
Array<T>::Array(size_t size, T value)
    :size_(size), capacity_(size)
{
    data_ = new T[size_];
    if (!data_)
    {
        std::cout << "Mem. allocation failed" << std::endl;
    }
    else
    {
        for(size_t i = 0; i < size_; ++i)
        {
            data_[i] = value;
        }
    }
    
}

template<typename T>
Array<T>::Array(const Array<T>& array)
{
    size_ = array.size();
    capacity_ = array.capacity();
    data_ = new T[capacity_];
    if (!data_)
    {
        std::cout << "Mem. allocation failed" << std::endl;
    }
    else
    {
        for(size_t idx = 0; idx < size_; ++idx)
        {
            data_[idx] = array[idx];
        }
    }
}

template<typename T>
inline size_t Array<T>::size() const
{
    return size_;
}

template<typename T>
inline size_t Array<T>::capacity() const
{
    return capacity_;
}

template<typename T>
inline Array<T>::iterator Array<T>::begin()
{
    return data_;
}

template<typename T>
inline Array<T>::iterator Array<T>::end()
{
    return (data_ + size_);
}

template<typename T>
inline T& Array<T>::front()
{
    return *(data_);
}

template<typename T>
inline T& Array<T>::back()
{
    return *(data_ + size_ - 1);
}

template<typename T>
inline const T& Array<T>::front() const
{
    return *(data_);
}

template<typename T>
inline const T& Array<T>::back() const
{
    return *(data_ + size_ - 1);
}

template<typename T>
void Array<T>::push_back(const T& value)
{
}
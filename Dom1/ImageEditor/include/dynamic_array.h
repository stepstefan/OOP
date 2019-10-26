// 
// dynamic_array.h
//
// Created by Stefan Stepanovic on 22/10/2019

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define _CONST_VECTOR_INCREMENT_ 5

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
    
    iterator begin();
    iterator end();
    inline T& front();
    inline T& back();
    inline const T& front() const;
    inline const T& back() const;

    void push_back(const T& value);
    void pop_back();

    T& operator[](size_t index);
    Array<T>& operator=(const Array<T>& array);

    // Misc
    void flip();
    void crop(size_t start_idx, size_t end_idx);

private:
    T* data_;
    size_t capacity_;
    size_t size_;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
// Add all definitions here because this is template class
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
            data_[idx] = array.data_[idx];
        }
    }
}

template<typename T>
Array<T>::~Array()
{
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
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

template <typename T>
inline bool Array<T>::empty() const
{
    return size_ == 0;
}

template<typename T>
typename Array<T>::iterator Array<T>::begin()
{
    return data_;
}

template<typename T>
typename Array<T>::iterator Array<T>::end()
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
void Array<T>::reserve(size_t capacity)
{
    T* data = new T[capacity_];
    if (!data)
    {
        std::cout << "Mem. allocation failed" << std::endl;
    }
    else
    {
        size_t new_size = capacity < size_ ? capacity : size_;
        for(size_t i = 0; i < new_size; ++i)
        {
            data[i] = data_[i];
        }
        capacity_ = capacity;
        size_ = new_size;
        delete[] data_;
        data_ = data;
    }
    
}

template<typename T>
void Array<T>::resize(size_t size)
{
    reserve(size);
    size_ = size;
}

template<typename T>
void Array<T>::push_back(const T& value)
{
    if (size_ >= capacity_)
    {
        reserve(capacity_ + _CONST_VECTOR_INCREMENT_);
    }
    data_[size_++] = value;
}

template<typename T>
void Array<T>::pop_back()
{
    size_--;
}

template<typename T>
void Array<T>::shrink_to_fit()
{
    capacity_ = size_;
    realloc(data_, size_*sizeof(T));
}

template<typename T>
T& Array<T>::operator[](size_t index)
{
    return *(data_ + index);
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& array)
{
    delete[] data_;
    data_ = new T[array.capacity()];
    if (!data_)
    {
        std::cout << "Mem. allocation failed" << std::endl;
    }
    else
    {
        size_ = array.size();
        capacity_ = array.capacity();
        for(size_t i = 0; i < size_; ++i)
        {
            data_[i] = array.data_[i];
        }
    }
    return *this;
}

template<typename T>
void Array<T>::crop(size_t start_idx, size_t end_idx)
{
    if (start_idx >= end_idx || start_idx < 0 || end_idx > size_)
    {
        std::cout << "Cannot crop from " << start_idx << " to " << end_idx << std::endl;
    }
    else
    {
        // Move all data from start_idx -> end_idx to beginning of array and resize it
        size_t new_size = end_idx - start_idx;
        for(size_t i = 0; i < new_size; ++i)
        {
            data_[i] = data_[start_idx + i];
        } 
        size_ = new_size;
        this->shrink_to_fit();
    }
}

template<typename T>
void Array<T>::flip()
{
    if(size_ == 0 || size_ == 1)
    {
        std::cout << "Nothing to flip" << std::endl;
    }
    else
    {
        typename Array<T>::iterator first = this->begin();
        typename Array<T>::iterator last = this->end() - 1;
        while(first < last)
        {
            T tmp = *first;
            *(first++) = *last;
            *(last--) = tmp;
        }   
    }
}

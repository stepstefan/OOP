// 
// dynamic_array.h
//
// Created by Stefan Stepanovic on 22/10/2019

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <type_traits>

#define _CONST_VECTOR_INCREMENT_ 5

template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };

template<typename T>
static void deleteIfPointer(const T& p)
{
    std::cout << "Nothing to delete" << std::endl;
}

template<typename T>
static void deleteIfPointer(T* p, bool pointer_to_array)
{
    std::cout << "Deleting" << std::endl;
    if (pointer_to_array)
    {
        delete[] p;
    }
    else
    {
        delete p;
    }
    
}
template<typename T, bool template_is_array> class Array;

namespace internal
{
    // Helper struct for memory management for all data types (typenames, classes, pointers and pointers to array)
    // Free all
    template<typename T, bool template_is_array>
    struct MemoryFreeHelper
    {
        static void freememory(Array<T, template_is_array>* that, size_t index)
        {
            // If it is non-pointer type (e.g. class) do nothing
            // delete[] data_ later will invoke destructors
        }
    };

    template<typename T, bool template_is_array>
    struct MemoryFreeHelper<T*, template_is_array>
    {
        static void freememory(Array<T*, template_is_array>* that, size_t index)
        {
            if (!that->empty())
            {
                // Free memory occupied by pointers (whether it is pointer to object or array of objects)
                for(size_t i = index; i < that->size(); ++i)
                {
                    if (template_is_array)
                    {
                        delete[] that->at(i);
                    }
                    else
                    {
                        delete that->at(i);
                    }
                }
            }
        }
    };
}


// Default dynamic array class
template<typename T, bool template_is_array=false>
class Array
{
public:
    typedef T* iterator;

// Constructors, destructor (self-explanatory)
    Array();
    explicit Array(size_t size);
    explicit Array(size_t size, T value);
    Array(const Array<T, template_is_array>& array);
    ~Array();

    // Free allocated memory in every way
    void freememory();

// Data access (self-explanatory)
    inline size_t size() const;
    inline size_t capacity() const;
    inline bool empty() const;
    
    void reserve(size_t capacity);
    void resize(size_t size);
    void clear();
    void shrink_to_fit();   
    
    iterator begin();
    iterator end();
    inline T& front();
    inline T& back();
    inline const T& front() const;
    inline const T& back() const;

    void push_back(const T& value);
    void pop_back();

    T& at(size_t index);

    T& operator[](size_t index);
    Array<T, template_is_array>& operator=(const Array<T, template_is_array>& array);

// Misc    
    // Flip array around its middle
    void flip();
    
    // Crop array from start to end index and resize it
    size_t crop(size_t start_idx, size_t end_idx);

    // Switch elements at index1 and index2
    void switch_elements(size_t index1, size_t index2);
    
    // Move element on position index to top of array (array size is same)
    void move_to_top(size_t index);
    
    // Swith element on position index with last element
    void switch_to_top(size_t index);

    // Move element on position index to the bottom of array (array size is same)    
    void move_to_bottom(size_t index);

    // Switch element on positin index with first element
    void switch_to_bottom(size_t index);

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
template<typename T, bool template_is_array>
Array<T, template_is_array>::Array()
    : size_(0), capacity_(0)
{}

template<typename T, bool template_is_array>
Array<T, template_is_array>::Array(size_t size)
    : size_(size), capacity_(size)
{
    data_ = new T[size];
    if (!data_)
    {
        std::cout << "Mem. allocation failed" << std::endl;
    }
}

template<typename T, bool template_is_array>
Array<T, template_is_array>::Array(size_t size, T value)
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

template<typename T, bool template_is_array>
Array<T, template_is_array>::Array(const Array<T, template_is_array>& array)
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

template<typename T, bool template_is_array>
void Array<T, template_is_array>::freememory()
{
    internal::MemoryFreeHelper<T, template_is_array>::freememory(this, 0);
    if (!this->empty())
    {
        delete[] data_;
    }
}

template<typename T, bool template_is_array>
Array<T, template_is_array>::~Array()
{
    freememory();
    size_ = 0;
    capacity_ = 0;
}


// Data acccess
template<typename T, bool template_is_array>
inline size_t Array<T, template_is_array>::size() const
{
    return size_;
}

template<typename T, bool template_is_array>
inline size_t Array<T, template_is_array>::capacity() const
{
    return capacity_;
}

template <typename T, bool template_is_array>
inline bool Array<T, template_is_array>::empty() const
{
    return capacity_ == 0;
}

template<typename T, bool template_is_array>
typename Array<T, template_is_array>::iterator Array<T, template_is_array>::begin()
{
    return data_;
}

template<typename T, bool template_is_array>
typename Array<T, template_is_array>::iterator Array<T, template_is_array>::end()
{
    return (data_ + size_);
}

template<typename T, bool template_is_array>
inline T& Array<T, template_is_array>::front()
{
    return *(data_);
}

template<typename T, bool template_is_array>
inline T& Array<T, template_is_array>::back()
{
    return *(data_ + size_ - 1);
}

template<typename T, bool template_is_array>
inline const T& Array<T, template_is_array>::front() const
{
    return *(data_);
}

template<typename T, bool template_is_array>
inline const T& Array<T, template_is_array>::back() const
{
    return *(data_ + size_ - 1);
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::reserve(size_t capacity)
{
    T* data = new T[capacity];
    if (!data)
    {
        std::cout << "Mem. allocation failed" << std::endl;
    }
    else
    {
        size_t new_size = capacity < size_ ? capacity : size_;
        if (!this->empty())
        {
            for(size_t i = 0; i < new_size; ++i)
            {
                data[i] = data_[i];
            }
            if (new_size < size_)
            {
                internal::MemoryFreeHelper<T, template_is_array>::freememory(this, new_size);
            }
            // free current memory and switch to newly created one
            delete[] data_;
        }
        capacity_ = capacity;
        size_ = new_size;
        data_ = data;
    }
    
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::resize(size_t size)
{
    reserve(size);
    size_ = size;
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::clear()
{
    size_ = 0;
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::push_back(const T& value)
{
    if (size_ >= capacity_)
    {
        reserve(capacity_ + _CONST_VECTOR_INCREMENT_);
    }
    data_[size_++] = value;
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::pop_back()
{
    if (size_ > 0)
    {
        internal::MemoryFreeHelper<T, template_is_array>::freememory(this, size_);
        size_--;
    }
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::shrink_to_fit()
{
    capacity_ = size_;
    reserve(size_);
}

template<typename T, bool template_is_array>
T& Array<T, template_is_array>::at(size_t index)
{
    if(index >= capacity_ || index >= size_)
    {
        std::cout << "Invalid index!" << std::endl;
        exit;
    }
    else
    {
        return *(data_ + index);
    }
}

template<typename T, bool template_is_array>
T& Array<T, template_is_array>::operator[](size_t index)
{
    return *(data_ + index);
}

template<typename T, bool template_is_array>
Array<T, template_is_array>& Array<T, template_is_array>::operator=(const Array<T, template_is_array>& array)
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


// Misc
template<typename T, bool template_is_array>
size_t Array<T, template_is_array>::crop(size_t start_idx, size_t end_idx)
{
    if (start_idx >= end_idx || start_idx < 0 || end_idx > size_)
    {
        std::cout << "Cannot crop from " << start_idx << " to " << end_idx << std::endl;
        return 0;
    }
    else
    {
        // Move all data from start_idx -> end_idx to beginning of array and resize it
        size_t new_size = end_idx - start_idx;
        for(size_t i = 0; i < new_size; ++i)
        {
            T tmp = this->at(i);
            this->at(i) = this->at(start_idx + i);
            this->at(start_idx + i) = tmp;
        }
        internal::MemoryFreeHelper<T, template_is_array>::freememory(this, new_size);
        capacity_ = new_size;
        size_ = new_size;
        return new_size;
    }
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::flip()
{
    if(size_ == 0 || size_ == 1)
    {
        std::cout << "Nothing to flip" << std::endl;
    }
    else
    {
        typename Array<T, template_is_array>::iterator first = this->begin();
        typename Array<T, template_is_array>::iterator last = this->end() - 1;
        while(first < last)
        {
            T tmp = *first;
            *(first++) = *last;
            *(last--) = tmp;
        }   
    }
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::switch_elements(size_t index1, size_t index2)
{
    if (index1 >= size_ || index2 >= size_)
    {
        std::cout << "Cannot access elements at positions " << index1 << " and " << index2 << std::endl << "Array unchanged" << std::endl;
    }
    else
    {  
        T tmp = this->at(index1);
        this->at(index1) = this->at(index2);
        this->at(index2) = tmp;
    }
    
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::switch_to_top(size_t index)
{
    this->switch_elements(index, size_ - 1);
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::switch_to_bottom(size_t index)
{
    this->switch_elements(index, 0);
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::move_to_top(size_t index)
{
    if (index >= size_)
    {
        std::cout << "Cannot move index " << index << std::endl << "Array unchanged" << std::endl; 
    }
    else
    {
        T tmp = this->at(index);
        size_t next = index + 1;
        for(; next < size_; ++next, ++index)
        {
            this->at(index) = this->at(next);
        }
        this->at(index) = tmp;
    }
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::move_to_bottom(size_t index)
{
    if (index >= size_)
    {
       std::cout << "Cannot move index " << index << std::endl << "Array unchanged" << std::endl; 
    }
    else
    {
        T tmp = this->at(index);
        size_t prev = index - 1;
        while(prev != 0)
        {
            this->at(index--) = this->at(prev--);
        }
        this->at(prev) = tmp;
    }
}
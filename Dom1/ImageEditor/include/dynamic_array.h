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
        if (p != NULL)
        {
            delete[] p;
            p = NULL;
        }
    }
    else
    {
        if (p != NULL)
        {
            delete p;
            p = NULL;
        }
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
            // If it is non-pointer type (e.g. class)
            // if (!that->empty())
            // {
            //     for(size_t i = index; i < that->size(); ++i)
            //     {
            //         // std::cout << "Destructor" << i << std::endl << std::flush;
            //         that->at(i).~T();   
            //     }
            // }
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
                        // std::cout << "Del[]" << std::endl << std::flush;
                        if (that->at(i) != NULL)
                        {
                            delete[] that->at(i);
                            that->at(i) = NULL;
                        }
                    }
                    else
                    {
                        if (that->at(i) != NULL)
                        {
                            // std::cout << "Del" << "\t" << std::flush;
                            delete that->at(i);
                            that->at(i) = NULL;
                        }
                    }
                }
                //std::cout << std::endl;
            }
        }
    };

    // template<typename T, bool template_is_array>
    // struct MemoryFreeHelper<Array<T, template_is_array>, template_is_array>
    // {
    //     static void freememory(Array<Array<T, template_is_array>, template_is_array>* that, size_t index)
    //     {
    //         if (!that->empty())
    //         {
    //             for(size_t i = index; i < that->size(); ++i)
    //             {
    //                 that->at(i).freememory();
    //             }
    //         }
    //     }
    // };

    template<typename T, bool template_is_array>
    struct CopyHelper
    {
        static void copy(const Array<T, template_is_array>& from, Array<T, template_is_array>* to,
                         size_t start_index, size_t end_index)
        {
            if (!from.empty())
            {
                to->resize(from.size());
                //to->reserve(from.capacity());
                for(size_t i = 0; i < from.size(); ++i)
                {
                    to->at(i) = from.at(i);
                }
            }
        }
    };

    template<typename T, bool template_is_array>
    struct CopyHelper<T*, template_is_array>
    {
        static void copy(const Array<T*, template_is_array>& from, Array<T*, template_is_array>* to,
                         size_t start_index, size_t end_index)
        {
            if (!from.empty())
            {
                to->resize(from.capacity());
                //to->reserve(from.capacity());
                for(size_t i = 0; i < from.size(); ++i)
                {
                    if(from.at(i) != NULL)
                    {
                        to->at(i) = new T(*(from.at(i)));
                    }
                    else
                    {
                        to->at(i) = NULL;
                    }
                    
                }
            }
        }
    };

    template<typename T, bool template_is_array>
    struct CopyHelper<Array<T, template_is_array>, template_is_array>
    {
        static void copy(const Array<Array<T, template_is_array>, template_is_array>& from, Array<Array<T, template_is_array>, template_is_array>* to,
                         size_t start_index, size_t end_index)
        {
            if (!from.empty())
            {
                to->resize(from.capacity());
                //to->reserve(from.capacity());
                for(size_t i = 0; i < from.size(); ++i)
                {
                    to->at(i).deep_copy(from.at(i));
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
    explicit Array(const size_t size);
    explicit Array(const size_t size, const T value);
    // Create this array and copy elements (not necessarily data elements are pointing to!)
    Array(const Array<T, template_is_array>& array);
    // TODO: add constructor that creates with deep_copy
    ~Array();

    // Free allocated memory in every way
    void freememory();

// Data access (self-explanatory)
    inline size_t size() const;
    inline size_t capacity() const;
    inline bool empty() const;
    
    void reserve(const size_t capacity);
    void resize(const size_t size);
    void clear();
    void shrink_to_fit();   
    
    iterator begin();
    iterator end();
    inline T& front();
    inline T& back();
    inline const T& front() const;
    inline const T& back() const;

    // Copies all data elements of vector are pointing to!
    void deep_copy(const Array<T, template_is_array>& array);

    void push_back(const T& value);
    void pop_back();

    T& at(const size_t index);
    const T& at(const size_t index) const;

    T& operator[](const size_t index);

    // BE CAREFUL this copies elements of array (not necessarily data it is pointing to)
    // different from deep copy
    Array<T, template_is_array>& operator=(const Array<T, template_is_array>& array);

// Misc    
    // Flip array around its middle
    void flip();
    
    // Crop array from start to end index and resize it
    size_t crop(const size_t start_idx, const size_t end_idx);

    // Switch elements at index1 and index2
    void switch_elements(const size_t index1, const size_t index2);
    
    // Move element on position index to top of array (array size is same)
    void move_to_top(const size_t index);
    
    // Swith element on position index with last element
    void switch_to_top(const size_t index);

    // Move element on position index to the bottom of array (array size is same)    
    void move_to_bottom(const size_t index);

    // Switch element on positin index with first element
    void switch_to_bottom(const size_t index);

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
    : size_(0), capacity_(0), data_(0)
{}

template<typename T, bool template_is_array>
Array<T, template_is_array>::Array(const size_t size)
    : size_(size), capacity_(size)
{
    data_ = new T[size];
    if (!data_)
    {
        std::cout << "Mem. allocation failed" << std::endl;
    }
}

template<typename T, bool template_is_array>
Array<T, template_is_array>::Array(const size_t size, const T value)
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
        // internal::CopyHelper<T, template_is_array>::copy(array, this, 0, array.size());
    }
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::deep_copy(const Array<T, template_is_array>& array)
{
    internal::CopyHelper<T, template_is_array>::copy(array, this, 0, array.size());
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::freememory()
{
    internal::MemoryFreeHelper<T, template_is_array>::freememory(this, 0);
}

template<typename T, bool template_is_array>
Array<T, template_is_array>::~Array()
{
    // Default destructor does not free all memory
    freememory();
    if(data_)
    {
        delete[] data_;
    }
    size_ = 0;
    capacity_ = 0;
    // std::cout << "Array destructed" << std::endl << std::flush;
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
void Array<T, template_is_array>::reserve(const size_t capacity)
{
    if (capacity <= capacity_)
    {
        size_t new_size = capacity < size_ ? capacity : size_;
        // free memory that is not being used anymore
        if (new_size < size_)
        {
            internal::MemoryFreeHelper<T, template_is_array>::freememory(this, new_size);
        }
        capacity_ = capacity;
        size_ = new_size;
    }
    else
    {
        T* data = new T[capacity];
        if (!data)
        {
            std::cout << "Mem. allocation failed" << std::endl;
        }
        else
        {
            if (!this->empty())
            {
                for(size_t i = 0; i < size_; ++i)
                {
                    data[i] = data_[i];
                }
                delete[] data_;
            }
            capacity_ = capacity;
            data_ = data;
        }
        
    }
    
    
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::resize(const size_t size)
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
    reserve(size_);
}

template<typename T, bool template_is_array>
T& Array<T, template_is_array>::at(const size_t index)
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
const T& Array<T, template_is_array>::at(const size_t index) const
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
T& Array<T, template_is_array>::operator[](const size_t index)
{
    return *(data_ + index);
}

template<typename T, bool template_is_array>
Array<T, template_is_array>& Array<T, template_is_array>::operator=(const Array<T, template_is_array>& array)
{
    if (!this->empty())
    {
        delete[] data_;
    }
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
size_t Array<T, template_is_array>::crop(const size_t start_idx, const size_t end_idx)
{
    if (start_idx >= end_idx || start_idx < 0 || end_idx > size_)
    {
        std::cout << "Cannot crop from " << start_idx << " to " << end_idx << std::endl;
        return 0;
    }
    else
    {
        // // Move all data from start_idx -> end_idx to beginning of array and resize it
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
        for(size_t i = 0; i < (size_t)(size_/2); ++i)
        {
            switch_elements(i, size_-1-i);
        }   
    }
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::switch_elements(const size_t index1, const size_t index2)
{
    if (index1 >= size_ || index2 >= size_)
    {
        std::cout << "Cannot access elements at positions " << index1 << " and " << index2 << std::endl << "Array unchanged" << std::endl;
    }
    else
    {  
        T* tmp = new T(this->at(index1)); // make it a pointer so when it goeas out of scope it doesn't destruct and delete all data inside
        this->at(index1) = this->at(index2);
        this->at(index2) = *tmp;
        
        // make it empty and destruct
        tmp = new T();
        delete tmp;
    }
    
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::switch_to_top(const size_t index)
{
    this->switch_elements(index, size_ - 1);
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::switch_to_bottom(const size_t index)
{
    this->switch_elements(index, 0);
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::move_to_top(const size_t index)
{
    if (index >= size_)
    {
        std::cout << "Cannot move index " << index << std::endl << "Array unchanged" << std::endl; 
    }
    else
    {
        size_t i = index;
        T* tmp = new T(this->at(index));
        size_t next = index + 1;
        for(; next < size_; ++next, ++i)
        {
            this->at(i) = this->at(next);
        }
        this->at(i) = *tmp;

        tmp = new T();
        delete tmp;
    }
}

template<typename T, bool template_is_array>
void Array<T, template_is_array>::move_to_bottom(const size_t index)
{
    if (index >= size_)
    {
       std::cout << "Cannot move index " << index << std::endl << "Array unchanged" << std::endl; 
    }
    else
    {
        T* tmp = new T(this->at(index));
        size_t i = index;
        size_t prev = index - 1;
        while(prev != 0)
        {
            this->at(i--) = this->at(prev--);
        }
        this->at(i) = this->at(prev);
        this->at(prev) = *tmp;

        tmp = new T();
        delete tmp;
    }
}
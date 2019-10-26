// 
// dynamic_array_test.cpp
//
// Created by Stefan Stepanovic on 24/10/2019

#include "include/dynamic_array.h"
#include <vector>

int main()
{
    Array<int*> a; 
    // a.pop_back();
    // a.push_back(2);
    // a.pop_back();

    Array<int> d(10);
    d.capacity();
    return 0;

    for(int i = 0; i < 10; ++i)
    {
        int* x = new int[1];
        *x = i;
        a.push_back(x);
    }
    // a.flip();
    // a.crop(1,3);
    std::cout << "Size " << a.size() << std::endl;
    std::cout << "Cap " << a.capacity() << std::endl;
    a.reserve(10);
    std::cout << "Size " << a.size() << std::endl;
    std::cout << "Cap " << a.capacity() << std::endl;
    for(auto& iterator : a)
    {
        std::cout << *iterator << std::endl;
    }

    std::cout << "MOVE " << a.size() << " " << a.capacity() << std::endl;
    //a.move_to_bottom(5);
    a.push_back(NULL);
    for(auto& iterator : a)
    {
        if(iterator == NULL)
        {
            std::cout << "NULL" << std::endl;
        }
        else
        {
            std::cout << *iterator << std::endl;
        }
        
    }
    for(auto& elem : a)
    {
        delete elem;
    }
    std::cout << "Size " << a.size() << "Cap " << a.capacity() << std::endl;
    a.clear();
    std::cout << sizeof(a[0]) << std::endl;
    a.shrink_to_fit();
    std::cout << sizeof(a[0]) << std::endl;
    std::cout << "Size " << a.size() << "Cap " << a.capacity() << std::endl;


    std::vector<int*> b(10);

    //b.shrink_to_fit();
    std::cout << "VECTORa" << b.size() << " " << b.capacity() << std::endl;

    b.at(5) = new int;
    a.at(5) = new int;


    // std::cout << a[50] << std::endl;
    // std::cout << a.at(50) << std::endl;
    return 0;
}
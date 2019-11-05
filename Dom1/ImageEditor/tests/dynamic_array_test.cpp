// 
// dynamic_array_test.cpp
//
// Created by Stefan Stepanovic on 24/10/2019

#include "include/dynamic_array.h"
#include <typeinfo>
#include <vector>
#include <string>

typedef struct helper
{
    int a;
} Helper;


int main()
{
    Array<int> a;
    a.resize(10);
    for(int i = 0; i < 10; ++i)
    {
        a[i] = i;
    }
    for(int i = 0; i < a.size(); ++i)
    {
        std::cout << a.at(i) << " " << std::endl;
    }
    std::cout << std::endl << std::endl;
    a.push_to_position(0, 100);
    for(int i = 0; i < a.size(); ++i)
    {
        std::cout << a.at(i) << " " << std::endl;
    }
    return 0;
}

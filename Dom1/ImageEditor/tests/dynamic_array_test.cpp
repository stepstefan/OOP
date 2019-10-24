// 
// dynamic_array.cpp
//
// Created by Stefan Stepanovic on 24/10/2019

#include "../include/dynamic_array.h"

int main()
{
    Array<int> a;
    a.push_back(1);
    a.push_back(2);
    a.pop_back();
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    //a.flip();
    a.crop(0,100);
    for(auto& iterator : a)
    {
        std::cout << iterator << std::endl;
    }
}
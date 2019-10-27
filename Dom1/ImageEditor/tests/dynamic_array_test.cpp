// 
// dynamic_array_test.cpp
//
// Created by Stefan Stepanovic on 24/10/2019

#include "include/dynamic_array.h"
#include <typeinfo>
#include <vector>

typedef struct helper
{
    int a;
    helper()
    {
        a = 0;
        std::cout << "Creating helper!" << std::endl << std::flush;
    }
    ~helper()
    {
        std::cout << "Delting helper!" << std::endl << std::flush;
    }
} Helper;


int main()
{
    Array<Helper*, true> a(10);
    for(size_t i = 0; i < 10; ++i)
    {
        a.push_back(new Helper[10]);
    }
    
    std::cout << "SINGLE" << std::endl;
    //Helper* h = new Helper();
    return 0;
}

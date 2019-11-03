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
    Array<Helper*> a;
    a.resize(10);
    for(size_t i = 0; i < a.size(); i++)
    {
        a.at(i) = new Helper();
    }
    std::string hex("AA1033");
    std::string rstr = hex.substr(0, 2);
    std::cout << rstr << " " << std::stoi(rstr, nullptr, 16) << std::endl;

    int tmp = 2;
    for(size_t j = 0; j < tmp; ++j)
    {
        a.push_back(NULL);
        a.push_front(NULL);
    }
    for(size_t i = 0; i < a.size(); ++i)
    {
        if(a.at(i) == NULL)
        {
            std::cout << "N" << std::endl;
        }
        else
        {
            std::cout << a.at(i)->a << std::endl;
        }
        
    }
    return 0;
}

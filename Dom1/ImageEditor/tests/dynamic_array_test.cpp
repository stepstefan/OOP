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
    Array<Array<int>> a(10, Array<int>(10));

    int cnt = 0;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            a.at(i).at(j) = cnt++;
        }
    } 

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            std::cout << a.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }

    a.crop(0,5);
    std::cout << "SINGLE" << std::endl;
    for(int i = 0; i < a.size(); i++)
    {
        for(int j = 0; j < a.at(i).size(); j++)
        {
            std::cout << a.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "SIZE Cap " << a.size() << " " << a.capacity() << std::endl;
    a.reserve(10);
    std::cout << "SIZE Cap " << a.size() << " " << a.capacity() << std::endl;
    a.reserve(3);

    for(int i = 0; i < a.size(); i++)
    {
        for(int j = 0; j < a.at(i).size(); j++)
        {
            std::cout << a.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "SIZE Cap " << a.size() << " " << a.capacity() << std::endl;

    a.pop_back();
    for(int i = 0; i < a.size(); i++)
    {
        for(int j = 0; j < a.at(i).size(); j++)
        {
            std::cout << a.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "SIZE Cap " << a.size() << " " << a.capacity() << std::endl;
    //Helper* h = new Helper();
    return 0;
}

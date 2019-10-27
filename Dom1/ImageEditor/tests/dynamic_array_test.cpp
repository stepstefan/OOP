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
    Array<int*> a(10);

    int cnt = 0;
    for(int i = 0; i < 10; i++)
    {
        int* x = new int;
        *x = cnt++;
        a.at(i) = x;
    } 

    std::cout << "A:" << std::endl;
    for(int i = 0; i < a.size(); ++i)
    {
        std::cout << a.at(i) << " ";
    }
    std::cout << std::endl << std::endl;

    Array<int*> b(a);

    std::cout << "A: ";
    for(int i = 0; i < a.size(); ++i)
    {
        std::cout << *a.at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "B: ";
    for(int i = 0; i < b.size(); ++i)
    {
        std::cout << *b.at(i) << " ";
    }
    std::cout << std::endl << std::endl;

    *a[5] = 100;
    
    std::cout << "A: ";
    for(int i = 0; i < a.size(); ++i)
    {
        std::cout << *a.at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "B: ";
    for(int i = 0; i < b.size(); ++i)
    {
        std::cout << *b.at(i) << " ";
    }
    std::cout << std::endl << std::endl;
  
    //Helper* h = new Helper();
    return 0;
}

//
// layer_test.cpp
//
// Created by Stefan Stepanovic on 24/10/2019

#include "include/layer.h"

int main()
{
    Pixel a;
    std::cout << int(a.r) << " " << int(a.g) << " " << int(a.b) << std::endl;

    Pixel* b = new Pixel(5, 6, 7);
    std::cout << int(b->r) << " " << int(b->g) << " " << int(b->b)<< std::endl;

    size_t width = 10;
    size_t height = 10;

    Layer layer(height, width);

    for(size_t i = 0; i < layer.height(); ++i)
    {
        for(size_t j = 0; j < layer.width(); ++j)
        {
            delete layer.at(i, j);    
            layer.at(i, j) = new Pixel(i,j,0); 
        }
    }



    for(size_t i = 0; i < layer.height(); ++i)
    {
        for(size_t j = 0; j < layer.width(); ++j)
        {
            std::cout << int(layer.at(i, j)->g) << " ";
        }
        std::cout << std::endl;
    }

    // layer.flipVertical();
    
    // std::cout << "After flip" << std::endl; 
    // for(size_t i = 0; i < layer.height(); ++i)
    // {
    //     for(size_t j = 0; j < layer.width(); ++j)
    //     {
    //         std::cout << int(layer.at(i, j)->g) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // layer.invert();

    // std::cout << "After invert" << std::endl; 
    // for(size_t i = 0; i < layer.height(); ++i)
    // {
    //     for(size_t j = 0; j < layer.width(); ++j)
    //     {
    //         std::cout << int(layer.at(i, j)->g) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    layer.crop(2, 2, 5, 3);

    std::cout << "After crop" << std::endl; 
    for(size_t i = 0; i < layer.height(); ++i)
    {
        for(size_t j = 0; j < layer.width(); ++j)
        {
            std::cout << int(layer.at(i, j)->g) << " " << std::flush;
        }
        std::cout << std::endl << std::flush;
    }
}
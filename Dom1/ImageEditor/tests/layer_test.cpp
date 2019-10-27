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

    Layer* layer= new Layer(height, width);

    for(size_t i = 0; i < layer->height(); ++i)
    {
        for(size_t j = 0; j < layer->width(); ++j)
        {
            if (layer->at(i, j) != NULL)
            {
                std::cout << int(layer->at(i, j)->r) << " " << std::flush;
            }
            else
            {
                std::cout << "N" << " ";
            }
            
        }
        std::cout << std::endl << std::flush;
    }

    for(size_t i = 0; i < layer->height(); ++i)
    {
        for(size_t j = 0; j < layer->width(); ++j)
        {
            delete layer->at(i, j);    
            layer->at(i, j) = new Pixel(i,j,0); 
        }
    }



    for(size_t i = 0; i < layer->height(); ++i)
    {
        for(size_t j = 0; j < layer->width(); ++j)
        {
            if (layer->at(i, j) != NULL)
            {
                std::cout << int(layer->at(i, j)->r) << " " << std::flush;
            }
            else
            {
                std::cout << "N" << " ";
            }
            
        }
        std::cout << std::endl << std::flush;
    }
    // layer.flipHorizontal();
    
    // std::cout << "After flip" << std::endl; 
    // for(size_t i = 0; i < layer.height(); ++i)
    // {
    //     for(size_t j = 0; j < layer.width(); ++j)
    //     {
    //         if (layer.at(i, j) != NULL)
    //         {
    //             std::cout << int(layer.at(i, j)->r) << " " << std::flush;
    //         }
    //         else
    //         {
    //             std::cout << "N" << " ";
    //         }
            
    //     }
    //     std::cout << std::endl << std::flush;
    // }

    // layer.move_to_bottom(layer.height() - 1);
    // std::cout << "After mv to bottom" << std::endl; 
    // for(size_t i = 0; i < layer.height(); ++i)
    // {
    //     for(size_t j = 0; j < layer.width(); ++j)
    //     {
    //         if (layer.at(i, j) != NULL)
    //         {
    //             std::cout << int(layer.at(i, j)->r) << " " << std::flush;
    //         }
    //         else
    //         {
    //             std::cout << "N" << " ";
    //         }
            
    //     }
    //     std::cout << std::endl << std::flush;
    // }

    // // layer.invert();

    // // std::cout << "After invert" << std::endl; 
    // // for(size_t i = 0; i < layer.height(); ++i)
    // // {
    // //     for(size_t j = 0; j < layer.width(); ++j)
    // //     {
    // //         std::cout << int(layer.at(i, j)->g) << " ";
    // //     }
    // //     std::cout << std::endl;
    // // }

    layer->crop(2, 0, 5, 10);
    // layer->eraseRect(2,2,3,3);

    std::cout << "After erase" << std::endl; 
    for(size_t i = 0; i < layer->height(); ++i)
    {
        for(size_t j = 0; j < layer->width(); ++j)
        {
            if (layer->at(i, j) != NULL)
            {
                std::cout << int(layer->at(i, j)->r) << " " << std::flush;
            }
            else
            {
                std::cout << "N" << " ";
            }
            
        }
        std::cout << std::endl << std::flush;
    }

    delete layer;

    // Pixel v(100,100,100);
    // layer.fillRect(2,2,3,3,v);

    // std::cout << "After fill" << std::endl; 
    // for(size_t i = 0; i < layer.height(); ++i)
    // {
    //     for(size_t j = 0; j < layer.width(); ++j)
    //     {
    //         if (layer.at(i, j) != NULL)
    //         {
    //             std::cout << int(layer.at(i, j)->r) << " " << std::flush;
    //         }
    //         else
    //         {
    //             std::cout << "N" << " ";
    //         }
            
    //     }
    //     std::cout << std::endl << std::flush;
    // }

    // Layer* l = new Layer;

}
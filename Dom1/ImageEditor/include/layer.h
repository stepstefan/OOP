// 
// layer.h
//
// Created by Stefan Stepanovic on 6/10/2019

#pragma once

#include "include/dynamic_array.h"

typedef unsigned char uchar; // value of pixel can be from 0 - 255

typedef struct pixel
{
    uchar r, g, b;

    pixel();
    pixel(uchar r, uchar g, uchar b);
    ~pixel();

    void invert();

    void toGray();
} Pixel;

// Default dynamic matrix class
// 2 dimensions
// This will be used as layer class!
class Layer
{
public:
    Layer();
    Layer(size_t height, size_t width);
    Layer(size_t height, size_t width, int opacity);
    
    ~Layer();

    Array<Pixel*>& row(size_t row);

    size_t height();
    size_t width();

    Pixel*& at(size_t height, size_t width);
    
    void invert();

    void flipVertical();
    void flipHorizontal();

    void crop(int x, int y, int w, int h);

    void fillRect(int x, int y, int w, int h, Pixel value);

    void ereaseRect(int x, int y, int w, int h);

private:
    Array<Array<Pixel*>> data_;
    size_t width_;
    size_t height_;
    int opacity_;
};
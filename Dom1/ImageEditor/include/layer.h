// 
// layer.h
//
// Created by Stefan Stepanovic on 26/10/2019

#pragma once

#include "include/dynamic_array.h"

typedef unsigned char uchar; // value of pixel can be from 0 - 255

typedef struct pixel
{
    uchar r, g, b;

    pixel();
    pixel(const uchar r, const uchar g, const uchar b);
    ~pixel();

    void set(const struct pixel& value);
    void set(const uchar r, const uchar g, const uchar b);

    void invert();

    void toGray();
} Pixel;

// Default dynamic matrix class
// 2 dimensions
// This will be used as layer class!
class Layer
{
public:
// Constructors, destructors
    Layer();
    Layer(const size_t height, const size_t width, const bool is_original=false);
    Layer(const size_t height, const size_t width, const int opacity, const bool is_original=false);
    
    ~Layer();

    void freememory();

// Data access
    Array<Pixel*>* row(size_t row);

    size_t height();
    size_t width();

    Pixel*& at(const size_t height, const size_t width);

    void reserve(const size_t capacity);

// Augmentation
    void invert();

    void flipVertical();
    void flipHorizontal();

    void move_to_top(const size_t index);
    void move_to_bottom(const size_t index);

    void crop(const int y, const int x, const int h, const int w);

    void fillRect(const int y, const int x, const int h, int w, const Pixel& value);

    void eraseRect(const int y, const int z, const int h, const int w);

    Layer& operator=(const Layer& layer);

private:
    Array<Array<Pixel*>*> data_;
    size_t width_;
    size_t height_;
    int opacity_;
    bool is_original_;
};
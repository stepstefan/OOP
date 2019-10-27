// 
// layer.cpp
//
// Created by Stefan Stepanovic on 6/10/2019

#include "include/layer.h"

void Pixel::invert()
{
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
}

void Pixel::toGray()
{

    r = g = b = uchar(0.3 * double(r) + 0.59 * double(g) + 0.11 * double(b));
}

Pixel::pixel()
    : r(0), g(0), b(0)
{}

Pixel::pixel(uchar r, uchar g, uchar b)
    : r(r), g(g), b(b)
{}

Pixel::~pixel()
{}

Layer::Layer()
    : width_(0), height_(0), opacity_(0)
{}

Layer::Layer(size_t width, size_t height)
    : width_(width), height_(height), opacity_(0),
      data_(height, Array<Pixel*, false>(width))
{
}

Layer::Layer(size_t width, size_t height, int opacity)
    : width_(width), height_(height), opacity_(opacity),
      data_(height, Array<Pixel*, false>(width))
{}

Layer::~Layer()
{
    for(auto& row : data_)
    {
        for(auto& pixel : row)
        {
            delete pixel;
        }
        row.clear();
        row.shrink_to_fit();
    }
    data_.clear();
    data_.shrink_to_fit();
    height_ = 0;
    width_ = 0;
    opacity_ = 0;
}

Array<Pixel*>& Layer::row(size_t row)
{
    if (row > height_)
    {
        std::cout << "Invalid row" << std::endl;
        exit;
    }
    else
    {
        return data_.at(row);
    }
}

size_t Layer::height()
{
    return height_;
}

size_t Layer::width()
{
    return width_;
}

Pixel*& Layer::at(size_t height, size_t width)
{
    if (height > height_ || width > width_)
    {
        std::cout << "Invalid indices" << std::endl;
        exit;
    }
    else
    {
        return data_.at(height).at(width);
    }
}

void Layer::invert()
{
    for(auto& row : data_)
    {
        for(auto& pixel : row)
        {
            pixel->invert();
        }
    }
}

void Layer::flipHorizontal()
{
    data_.flip();
}

void Layer::flipVertical()
{
    for(auto& row : data_)
    {
        row.flip();
    }
}

void Layer::crop(int x, int y, int w, int h)
{
    if(x < 0 || y < 0 || w < 0 || h < 0 ||
       (x + w) > width_ || (y + h) > height_)
    {
        std::cout << "Invalid crop arguments" << std::endl;
    }
    else
    {
        // First crop rows so less crops are performed by columns
        // height_ = data_.crop(size_t(y), size_t(y + h));
        // if (height_ != h)
        // {
        //     std::cout << "Unknown crop error!" << std::endl;
        // }
        // else
        {
            size_t new_width = (size_t)(w);
            for(auto& row : data_)
            {
                width_ = row.crop(size_t(x), size_t(x + w));
                if (width_ != new_width)
                {
                    std::cout << "Unknown crop error" << std::endl;
                }
            }
            height_ = data_.crop(size_t(y), size_t(y+h));
        }
    }
}
// 
// layer.cpp
//
// Created by Stefan Stepanovic on 6/10/2019

#include "include/layer.h"

Pixel::pixel()
    : r(0), g(0), b(0)
{
    //
}

Pixel::pixel(const uchar r, const uchar g, const uchar b)
    : r(r), g(g), b(b)
{
    //
}

Pixel::~pixel()
{
    // Do nothing
}

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

void Pixel::set(const Pixel& value)
{
    this->r = value.r;
    this->g = value.g;
    this->b = value.b;
}

void Pixel::set(const uchar r, const uchar g, const uchar b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Layer::Layer()
    : width_(0), height_(0), opacity_(0), data_()
{
}

Layer::Layer(const size_t width, const size_t height, const int opacity)
    : width_(width), height_(height), opacity_(opacity)
{
    data_.reserve(height_);
    for(size_t i = 0; i < height; ++i)
    {
        data_.push_back(new Array<Pixel*, false>(width));
        for(size_t j = 0; j < width; ++j)
        {
            data_.at(i)->at(j) = NULL;
        }
    }
}

Layer::~Layer()
{
    // No need for invoking deconstructor of array (it will automatically be called)
    data_.freememory();
    height_ = 0;
    width_ = 0;
    opacity_ = 0;
}

void addPadding(Array<Array<Pixel*>*>& data, size_t padding_y, size_t padding_x)
{
    for(size_t i = 0; i < data.size(); ++i)
    {
        for(size_t j = 0; j < padding_x; ++j)
        {
            data.at(i)->push_back(NULL);
            data.at(i)->push_front(NULL);
        }
    }
    for(size_t j = 0; j < padding_y; ++j)
    {
        Array<Pixel*>* rowf = new Array<Pixel*>(data.at(0)->size(), NULL);
        Array<Pixel*>* rowb = new Array<Pixel*>(data.at(0)->size(), NULL);
        data.push_front(rowf);
        data.push_back(rowb);
    }
}

void Layer::freememory()
{
    data_.freememory();
}

Array<Pixel*>* Layer::row(const size_t row)
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

Pixel*& Layer::at(const size_t height, const size_t width)
{
    if (height > height_ || width > width_)
    {
        // std::cout << "Invalid indices" << std::endl;
        exit;
    }
    else
    {
        return data_.at(height)->at(width);
    }
}

Layer& Layer::operator=(const Layer& layer)
{
    data_ = layer.data_;
    height_ = layer.height_;
    width_ = layer.width_;
    opacity_ = layer.opacity_;
}

void Layer::reserve(const size_t capacity)
{
    data_.reserve(capacity);
    height_ = data_.size();
}

void Layer::invert()
{
    for(auto& row : data_)
    {
        for(auto& pixel : *row)
        {
            pixel->invert();
        }
    }
}

void Layer::toGray()
{
    for(auto& row : data_)
    {
        for(auto& pixel : *row)
        {
            pixel->toGray();
        }
    }
}

void Layer::flipVertical()
{
    data_.flip();
}

void Layer::flipHorizontal()
{
    for(auto& row : data_)
    {
        row->flip();
    }
}

void Layer::setOpacity(int opacity)
{
    opacity_ = opacity;
}

void Layer::move_to_bottom(const size_t index)
{
    data_.move_to_bottom(index);
}

void Layer::move_to_top(const size_t index)
{
    data_.move_to_top(index);
}


// Beware! Kernel size must be equal to [h, w]
Pixel applyKernel(const Array<Array<Pixel*>*>& data, double** kernel, size_t y, size_t x, size_t h, size_t w)
{
    double r = 0;
    double g = 0;
    double b = 0;
    for(size_t i = 0; i < h; ++i)
    {
        for(size_t j = 0; j < w; ++j)
        {
            if(data.at(i+y)->at(j+x) != NULL)
            {
                r += double(data.at(i+y)->at(j+x)->r) * kernel[i][j];
                g += double(data.at(i+y)->at(j+x)->g) * kernel[i][j];
                b += double(data.at(i+y)->at(j+x)->b) * kernel[i][j];
            }
        }
    }
    uchar rval = uchar(r);
    uchar gval = uchar(g);
    uchar bval = uchar(b);
    Pixel out(rval, gval, bval);
    return out;
}

double** createMeanKernel(const Array<Array<Pixel*>*>& data, size_t y, size_t x, size_t h, size_t w)
{
    int cnt = 0;
    for(size_t i = y; i < y+h; ++i)
    {
        for(size_t j = x; j < x+w; ++j)
        {
            if(data.at(i)->at(j) != NULL)
            {
                cnt++;
            }
        }
    }
    double** out = new double*[h];
    for(size_t i = 0; i < h; ++i)
    {
        out[i] = new double[w];
        for(size_t j = 0; j < w; ++j)
        {
            out[i][j] = 1.0/cnt;
        }
    }
    return out;
}

void Layer::blur(const size_t kernel_size)
{
    size_t padding_x = kernel_size;
    size_t padding_y = padding_x;

    Array<Array<Pixel*>*> copy_data(height_);
    copy_data.deep_copy(data_);
    std::cout << copy_data.size() << std::endl;
    addPadding(copy_data, padding_y, padding_x);
    for(size_t i = 0; i < height_; ++i)
    {
        for(size_t j = 0; j < width_; ++j)
        {
            double** kernel = createMeanKernel(copy_data, i, j, kernel_size*2+1, kernel_size*2+1);
            Pixel new_value = applyKernel(copy_data, kernel, i, j, kernel_size*2+1, kernel_size*2+1);
            data_.at(i)->at(j)->set(new_value);
        }   
    }
}

tuple<size_t> Layer::crop(const int y, const int x, const int h, const int w)
{
    if(x < 0 || y < 0 || w < 0 || h < 0 ||
       (x + w) > width_ || (y + h) > height_)
    {
        std::cout << "Invalid crop arguments. Layer unchanged!" << std::endl;
    }
    else
    {
        // First crop rows so less crops are performed by columns
        height_ = data_.crop(size_t(y), size_t(y + h));
        if (height_ != h)
        {
            std::cout << "Unknown height crop error!" << std::endl;
        }
        else
        {
            size_t new_width = (size_t)(w);
            for(auto& row : data_)
            {
                width_ = row->crop(size_t(x), size_t(x + w));
                if (width_ != new_width)
                {
                    std::cout << "Unknown width crop error" << std::endl;
                }
            }
        }
    }
    tuple<size_t> shape;
    shape.set(height_, width_);
}

void Layer::fillRect(const int y, const int x, const int h, const int w, const Pixel& value)
{
    if(x < 0 || y < 0 || w < 0 || h < 0 ||
       (x + w) > width_ || (y + h) > height_)
    {
        std::cout << "Invalid rectangle arguments. Layer unchanged!" << std::endl;
    }
    else
    {
        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                if (data_.at(i + y)->at(j + x) != NULL)
                {
                    data_.at(i + y)->at(j + x)->set(value);
                }
                else
                {
                    data_.at(i + y)->at(j + x) = new Pixel(value);
                }
                
            }
        }
    }
    
}

void Layer::eraseRect(const int y, const int x, const int h, const int w)
{
    if(x < 0 || y < 0 || w < 0 || h < 0 ||
       (x + w) > width_ || (y + h) > height_)
    {
        std::cout << "Invalid rectangle arguments. Layer unchanged!" << std::endl;
    }
    else
    {
        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                delete data_.at(i + y)->at(j + x);
                data_.at(i + y)->at(j + x) = NULL;
            }
        }
    }
}
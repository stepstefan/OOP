// 
// ImageEditor.cpp
//
// Created by Stefan Stepanovic on 27/10/2019

#include "include/ImageEditor.h"
#include <cstring>

// Constructor, Destructor
ImageEditor::ImageEditor()
    : active_pixel_value(), data_()
{}

ImageEditor::~ImageEditor()
{
    // Will automatically destruct array freeing all of it's memory
}

// Private methods
void ImageEditor::findIntersection(int& x, int& y, int& w, int& h)
{
    
}



// Public methods
bool ImageEditor::loadImage(unsigned char* image)
{
    image_ = image;
    if(image[0] != 'B' || image[1] != 'M' || image[2] != '=')
    {
        std::cout << "Invalid start format" << std::endl;
    }
    else
    {
        int i = 3;
        name_ = "";
        while(image[i] != '=')
        {
            name_.push_back(image[i++]);
        }
        i++;
        while((i % 4) != 0)
        {
            i++;
        }
        width_ = height_ = 0;
        for(int j = 0; j < 4; j++)
        {
            width_ += int(image[i + j] * pow(16, j));
        }
        i += 4;
        for(int j = 0; j < 4; j++)
        {
            height_ += int(image[i + j] * pow(16, j));
        }
        i += 4;
        this->data_.push_back(new Layer(height_, width_, true));
        for(int h = height_ - 1; h >= 0; --h)
        {
            for(int w = 0; w < width_; ++w)
            {
                uchar b = image[i++];
                uchar g = image[i++];
                uchar r = image[i++];
                data_.at(0)->at(h, w) = new Pixel(r, g, b);
            }
            while((i % 4) != 0)
            {
                i++;
            }
        }
        std::cout << name_ << " " << width_ << " " << height_ << i << std::endl;
    }
    
}

unsigned char* ImageEditor::saveImage()
{
    Layer* final = data_.at(0);
    int output_length = 4 + name_.length();
    output_length += (4 - (output_length % 4)); // fill to number divisible by 4
    output_length += 8;
    int len_of_row = 3 * width_;
    len_of_row += (4 - (len_of_row % 4)) % 4; // fill to number divisible by 4
    output_length += height_ * len_of_row;
    std::cout << "Output string len = " << output_length << std::endl;

    // unsigned char* output = new unsigned char[output_length];
    unsigned char* output = (unsigned char*)calloc(output_length, sizeof(unsigned char));
    output[0] = (unsigned char)('B');
    output[1] = (unsigned char)('M');
    output[2] = (unsigned char)('=');
    for(int c = 0; c < name_.length(); ++c)
    {
        output[3 + c] = (unsigned char)(name_[c]);
    }
    int i = 3 + name_.length();
    output[i++] = (unsigned char)('=');
    while((i % 4) != 0)
    {
        i++;
    } // fill to number divisible by 4
    size_t tmp = width_;
    for(int j = 0; j < 4; ++j)
    {
        output[i++] = (unsigned char)(tmp % 256);
        tmp = size_t(tmp / 256);
    }
    tmp = height_;
    for(int j = 0; j < 4; ++j)
    {
        output[i++] = (unsigned char)(tmp % 256);
        tmp = size_t(tmp / 256);
    }
    for(int h = height_ - 1; h >= 0; --h)
    {
        for(int w = 0; w < width_; ++w)
        {
            output[i++] = final->at(h, w)->b;
            output[i++] = final->at(h, w)->g;
            output[i++] = final->at(h, w)->r;
        }
        while((i % 4) != 0)
        {
            i++;
        }
    }
    for(int c = 0; c < 20; ++c)
    {
        if(output[c] != image_[c])
        {
            std::cout << c << "|" << output[c] << "|" << image_[c] << std::endl;
        }
    }

    return output;
}

void ImageEditor::addLayer()
{
    Layer* l = new Layer(height_, width_);
    data_.push_back(l);
}

void ImageEditor::deleteLayer()
{
    data_.back()->freememory();
    data_.pop_back();
}

void ImageEditor::selectLayer(int i)
{
    if (i >= data_.size())
    {
        std::cout << "Invalid index of layer. Image unchanged!" << std::endl;
    }
    else
    {
        data_.move_to_top(i);
    }
    
}

void ImageEditor::setLayerOpacity(int opacity)
{
    data_.back()->setOpacity(opacity);
}

void ImageEditor::invertColors()
{
    for(auto& layer : data_)
    {
        layer->invert();
    }
}

void ImageEditor::toGrayScale()
{
    for(auto& layer : data_)
    {
        layer->toGray();
    }
}

void ImageEditor::blur(int size)
{}

void ImageEditor::flipHorizontal()
{
    for(auto& layer : data_)
    {
        layer->flipHorizontal();
    }
}

void ImageEditor::flipVertical()
{
    for(auto& layer : data_)
    {
        layer->flipVertical();
    }
}

void ImageEditor::crop(int x, int y, int w, int h)
{
    findIntersection(x, y, w, h);
    for(auto& layer : data_)
    {
        layer->crop(y, x, h, w);
    }
}

void ImageEditor::setActiveColor(std::string hex)
{}

void ImageEditor::fillRect(int x, int y, int w, int h)
{
    findIntersection(x, y, w, h);
    data_.back()->fillRect(y, x, h, w, active_pixel_value);
}

void ImageEditor::eraseRect(int x, int y, int w, int h)
{
    findIntersection(x, y, w, h);
    if (data_.back()->isOriginal())
    {
        std::cout << "Cannot erase on original layer! Image unchanged" << std::endl;
    }
    else
    {
        data_.back()->eraseRect(y, x, h, w);
    }
}


// 
// ImageEditor.cpp
//
// Created by Stefan Stepanovic on 27/10/2019

#include "include/ImageEditor.h"

ImageEditor::ImageEditor()
    : active_pixel_value(), data_()
{}

ImageEditor::~ImageEditor()
{
    // Will automatically destruct array freeing all of it's memory
}

bool ImageEditor::loadImage(unsigned char* image)
{
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
            width_ += int(image[i + j]);
        }
        i += 4;
        for(int j = 0; j < 4; j++)
        {
            height_ += int(image[i + j]);
        }
        i += 4;
        this->data_.push_back(new Layer(height_, width_));
        for(int h = 0; h < height_; ++h)
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
        std::cout << name_ << " " << width_ << " " << height_  << " Iterator = " << i << std::endl;
    }
    
}

unsigned char* ImageEditor::saveImage()
{
    Layer* final = data_.at(0);
    int output_length = 3 + name_.length();
    output_length += (4 - (output_length % 4)); // fill to number divisible by 4
    output_length += 8;
    int len_of_row = 3 * width_;
    len_of_row += (4 - (len_of_row % 4)) % 4; // fill to number divisible by 4
    output_length += height_ * len_of_row;
    std::cout << "Output string len = " << output_length << std::endl;

    unsigned char* output = new unsigned char[output_length];
    output[0] = 'B';
    output[1] = 'M';
    output[2] = '=';
    for(char s : name_)
    {
        output += (unsigned char)(s);
    }
    int i = 3 + name_.length();
    output[i++] = '=';

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
}

void ImageEditor::setLayerOpacity(int opacity)
{}

void ImageEditor::invertColors()
{}

void ImageEditor::toGrayScale()
{}

void ImageEditor::blur(int size)
{}

void ImageEditor::flipHorizontal()
{}

void ImageEditor::flipVertical()
{}

void ImageEditor::crop(int x, int y, int w, int h)
{}

void ImageEditor::setActiveColor(std::string hex)
{}

void ImageEditor::fillRect(int x, int y, int w, int h)
{}

void ImageEditor::eraseRect(int x, int y, int w, int h)
{}


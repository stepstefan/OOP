// 
// ImageEditor.cpp
//
// Created by Stefan Stepanovic on 27/10/2019

#include "include/ImageEditor.h"
#include <string>

// Constructor, Destructor
ImageEditor::ImageEditor()
    : active_pixel_value(0, 0, 0), data_()
{}

ImageEditor::~ImageEditor()
{
    // Will automatically destruct array freeing all of it's memory
}

// Private methods
void ImageEditor::findIntersection(int& x, int& y, int& w, int& h)
{
    if (x < 0)
    {
        w -= x;
        x = 0;
    }
    if (y < 0)
    {
        h -= y;
        y = 0;
    }

    if (x+w > width_)
    {
        w = width_ - x;
    }
    if (y+h > height_)
    {
        h = width_ - y;
    }
    
    if (x > width_)
    {
        x = w = 0;
    }
    if (y > height_)
    {
        y = h = 0;
    }
}

Layer* ImageEditor::mergeLayers()
{
    Layer* final = new Layer(height_, width_);
    for(size_t i = 0; i < height_; ++i)
    {
        for(size_t j = 0; j < width_; ++j)
        {
            double red = 0;
            double green = 0;
            double blue = 0;

            double percent = 1.0;
            
            for(int layer = data_.size()-1; layer >= 0; --layer)
            {
                if(data_.at(layer)->at(i, j) != NULL)
                {
                    red += (double(percent) * double(data_.at(layer)->opacity()) * double(data_.at(layer)->at(i, j)->r));
                    green += (double(percent) * double(data_.at(layer)->opacity()) * double(double(data_.at(layer)->at(i, j)->g)));
                    blue += (double(percent) * double(data_.at(layer)->opacity()) * double(data_.at(layer)->at(i, j)->b));

                    percent *= (1.0 - data_.at(layer)->opacity());
                }
            }
            final->at(i, j) = new Pixel(uchar(red), uchar(green), uchar(blue));
        }
    }
    std::cout << "Created final" << std::endl;
    return final;
}


// Public methods
bool ImageEditor::loadImage(unsigned char* image)
{
    if(image[0] != 'B' || image[1] != 'M' || image[2] != '=')
    {
        std::cout << "Invalid start format" << std::endl;
    }
    else
    {
        // get name and format
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

        // get width and height
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
        
        // get data
        this->data_.push_back(new Layer(height_, width_));
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
        std::cout << name_ << " " << width_ << " " << height_ << std::endl;
        active_index_ = 0;
    }
}

unsigned char* ImageEditor::saveImage()
{
    Layer* final = mergeLayers();
    int output_length = 4 + name_.length();
    output_length += (4 - (output_length % 4)); // fill to number divisible by 4
    output_length += 8;
    int len_of_row = 3 * width_;
    len_of_row += (4 - (len_of_row % 4)) % 4; // fill to number divisible by 4
    output_length += height_ * len_of_row;
    std::cout << "New image size: " << this->height_ << " " << this->width_ << std::endl;
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

    return output;
}

void ImageEditor::addLayer()
{
    Layer* l = new Layer(height_, width_);
    data_.push_to_position(active_index_++, l);
}

void ImageEditor::deleteLayer()
{
    if (active_index_ == 0)
    {
        std::cout << "Cannot delete original layer. Image unchanged!" << std::endl;
    }
    else
    {
        data_.move_to_top(active_index_);
        data_.back()->freememory();
        data_.pop_back();
    }
}

void ImageEditor::selectLayer(int i)
{
    if (i >= data_.size())
    {
        std::cout << "Invalid index of layer. Image unchanged!" << std::endl;
    }
    else
    {
        active_index_ = size_t(i);
    }
    
}

void ImageEditor::setLayerOpacity(int opacity)
{
    data_.at(active_index_)->setOpacity(opacity);
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
{
    data_.at(active_index_)->blur(size_t(size));
}

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
    height_ = h;
    width_ = w;
    for(auto& layer : data_)
    {
        tuple<size_t> new_shape = layer->crop(size_t(y), size_t(x), size_t(h), size_t(w));
        if (height_ != new_shape.first)
        {
            std::cout << "Hight mismatch!" << std::endl;
        }
        if (width_ != new_shape.second)
        {
            std::cout << "Width mismatch" << std::endl;
        }
    }
}

void ImageEditor::setActiveColor(std::string hex)
{
    if(hex[0] != '#')
    {
        std::cout << "Invalid hex format" << std::endl;
    }
    else
    {
        std::string tmp = hex.substr(1, 2);
        uchar rval = uchar(std::stoi(tmp, nullptr, 16));
        tmp = hex.substr(3, 2);
        uchar gval = uchar(std::stoi(tmp, nullptr, 16));
        tmp = hex.substr(5, 2);
        uchar bval = uchar(std::stoi(tmp, nullptr, 16));

        active_pixel_value.set(rval, gval, bval);
    }
}

void ImageEditor::fillRect(int x, int y, int w, int h)
{
    findIntersection(x, y, w, h);
    data_.at(active_index_)->fillRect(y, x, h, w, active_pixel_value);
}

void ImageEditor::eraseRect(int x, int y, int w, int h)
{
    findIntersection(x, y, w, h);
    if (active_index_ == 0)
    {
        std::cout << "Cannot erase on original layer! Image unchanged" << std::endl;
    }
    else
    {
        data_.at(active_index_)->eraseRect(y, x, h, w);
    }
}
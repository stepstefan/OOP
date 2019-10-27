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
    // Will automatically call all destructors of objects
}

void ImageEditor::addLayer()
{
    Layer l(height_, width_);
    data_.push_back(l);
}

void ImageEditor::deleteLayer()
{
    data_.pop_back();
}
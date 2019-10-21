// 
// ImageEditor.h
//
// Created by Stefan Stepanovic on 22/10/2019

#pragma once

#include <stdlib.h>
#include <string>

#define MAX 2^32


// Main class for Image operations
class ImageEditor
{
public:
// Image input/output
    // Load image from string format
    bool loadImage(unsigned char* image);
    
    // Save image in string format
    unsigned char* saveImage();

// Image layering    
    // Add layer on top of existing layers (new one becomes active)
    void addLayer();
    
    // Delete currently active layer
    void deleteLayer();
    
    // Select new active layer from existing layers
    void selectLayer(int i);
    
    // Set opacity of currently active layer
    void setLayerOpacity(int opacity);

// Image manipulation
    // Invert color of all pixels of active layer
    void invertColors();
    
    // Convert all colors of active layer of image to grayscale
    void toGrayScale();
    
    // Blur image. Apply mean filter with kernel size $size
    void blur(int size);

    // Rotate image pixels by y exis
    void flipHorizontal();
    
    // Rotate image pixels by x axis
    void flipVertical();

    // Crop image from point (x, y) with size (with $w, height $h)
    void crop(int x, int y, int w, int h);

// Drawing
    // Set color for drawing
    void setActiveColor(std::string hex);
    
    // Fil rectangle with selected color from point (x, y) with size (width $w, height $h)
    void fillRect(int x, int y, int w, int h);

    // Remove pixels in rectangle from point (x, y) with size (sidth $w, height $h)
    void eraseRect(int x, int y, int w, int h);

private:

};

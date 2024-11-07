/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#ifndef BMPSERVICE_H
#define BMPSERVICE_H

#include "BMPImage.h"

class BMPService {
public:
    static BMPImage rotateClockwise(BMPImage& image);
    static BMPImage rotateCounterclockwise(BMPImage& image);
    static BMPImage applyGaussianFilter(BMPImage& image);
};

#endif 

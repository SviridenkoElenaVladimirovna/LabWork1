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
